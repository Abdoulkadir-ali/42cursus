import os
import struct
import zlib
import sys

# FBX Binary to ASCII Converter (Standalone Pure Python)
# Built for miniRT project to handle binary FBX files from sources like Mixamo or Sketchfab.

class FbxNode:
    def __init__(self, name=""):
        self.name = name
        self.properties = []
        self.children = []

    def __repr__(self):
        return f"Node({self.name}, props={len(self.properties)}, children={len(self.children)})"

def read_string(f, length):
    return f.read(length).decode('utf-8', errors='ignore')

def read_property(f):
    type_data = f.read(1)
    if not type_data: return None
    type_char = type_data.decode('ascii')
    
    if type_char == 'I': return struct.unpack('<i', f.read(4))[0]
    if type_char == 'L': return struct.unpack('<q', f.read(8))[0]
    if type_char == 'F': return struct.unpack('<f', f.read(4))[0]
    if type_char == 'D': return struct.unpack('<d', f.read(8))[0]
    if type_char == 'S':
        data = f.read(4)
        if len(data) < 4: return None
        length = struct.unpack('<I', data)[0]
        return f.read(length).decode('utf-8', errors='ignore')
    if type_char == 'R':
        data = f.read(4)
        if len(data) < 4: return None
        length = struct.unpack('<I', data)[0]
        return f.read(length) # raw binary data
    
    # Array types
    if type_char in 'ilfdcb':
        data = f.read(12)
        if len(data) < 12: return None
        array_len, encoding, compressed_len = struct.unpack('<III', data)
        
        data = f.read(compressed_len)
        return {'type': type_char, 'len': array_len, 'encoding': encoding, 'data': data}
    
    return None

def parse_fbx_binary(filepath):
    with open(filepath, 'rb') as f:
        header = f.read(23)
        if not header.startswith(b'Kaydara FBX Binary'):
            print(f"Error: {filepath} is not a valid FBX Binary file.")
            return None
        
        version = struct.unpack('<I', f.read(4))[0]
        off_fmt = '<Q' if version >= 7500 else '<I'
        off_size = 8 if version >= 7500 else 4
        null_size = 25 if version >= 7500 else 13
        
        root = FbxNode("Root")
        
        def read_node_children(parent, end_offset):
            while f.tell() < end_offset:
                cur_pos = f.tell()
                data = f.read(off_size)
                if len(data) < off_size: break
                child_end = struct.unpack(off_fmt, data)[0]
                if child_end == 0: break # Null record
                
                num_props = struct.unpack(off_fmt, f.read(off_size))[0]
                prop_list_len = struct.unpack(off_fmt, f.read(off_size))[0]
                name_len_data = f.read(1)
                if not name_len_data: break
                name_len = struct.unpack('<B', name_len_data)[0]
                name = read_string(f, name_len)
                
                node = FbxNode(name)
                for _ in range(num_props):
                    p = read_property(f)
                    if p is not None:
                        node.properties.append(p)
                
                if f.tell() < child_end:
                    read_node_children(node, child_end)
                
                parent.children.append(node)
                f.seek(child_end)

        file_size = os.path.getsize(filepath)
        # FBX files have a sentinel at the very end
        read_node_children(root, file_size - null_size)
        return root

def write_fbx_ascii(node, f, indent=0):
    if node.name == "Root":
        for child in node.children:
            write_fbx_ascii(child, f, indent)
        return

    ind = "  " * indent
    f.write(f"{ind}{node.name}: ")
    
    for i, p in enumerate(node.properties):
        if i > 0: f.write(", ")
        if isinstance(p, str): f.write(f'"{p}"')
        elif isinstance(p, dict) and 'type' in p: # Array
            data = p['data']
            if p['encoding'] == 1:
                data = zlib.decompress(data)
            
            fmt_map = {'i': 'i', 'l': 'q', 'f': 'f', 'd': 'd', 'b': '?', 'c': 'b'}
            type_char = p['type'].lower()
            fmt = '<' + fmt_map[type_char]
            
            f.write(f"*{p['len']} {{\n{ind}  a: ")
            stride = struct.calcsize(fmt)
            for j in range(p['len']):
                start = j * stride
                end = (j + 1) * stride
                if end > len(data): break
                val = struct.unpack(fmt, data[start:end])[0]
                f.write(str(val))
                if j < p['len'] - 1:
                    f.write(",")
                    if j % 10 == 9: f.write(f"\n{ind}    ")
            f.write(f"\n{ind}  }}")
        else: f.write(str(p))
    
    if node.children:
        f.write(" {\n")
        for child in node.children:
            write_fbx_ascii(child, f, indent + 1)
        f.write(ind + "}\n")
    else:
        f.write("\n")

def convert(src, dest):
    print(f"Converting {src} -> {dest}")
    root = parse_fbx_binary(src)
    if root:
        with open(dest, 'w') as f:
            f.write("; FBX ASCII Generated by miniRT fbx_converter\n")
            f.write("FBXHeaderExtension:  {\n  FBXHeaderVersion: 1003\n  FBXVersion: 7400\n}\n")
            write_fbx_ascii(root, f)
        print("Conversion successful.")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python fbx_converter.py <file.fbx>")
        sys.exit(1)
    
    input_path = sys.argv[1]
    if os.path.isdir(input_path):
        for root_dir, dirs, files in os.walk(input_path):
            for file in files:
                if file.endswith(".fbx"):
                    full_path = os.path.join(root_dir, file)
                    convert(full_path, full_path.replace(".fbx", "_ascii.fbx"))
    else:
        convert(input_path, input_path.replace(".fbx", "_ascii.fbx"))
