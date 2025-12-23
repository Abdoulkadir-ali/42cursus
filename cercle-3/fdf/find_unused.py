import os
import re

def get_function_prototypes(header_dir):
    prototypes = []
    # Regex for a typical C function prototype: return_type function_name(args);
    # This is a simple regex and might miss complex cases or match macros, but it's a good start.
    # It assumes nice formatting (norminette).
    # Matches: int foo(
    name_pattern = re.compile(r'^\s*[a-zA-Z_][a-zA-Z0-9_*]+\s+\**([a-zA-Z_][a-zA-Z0-9_]*)\s*\(')
    
    for filename in os.listdir(header_dir):
        if filename.endswith(".h"):
            with open(os.path.join(header_dir, filename), 'r') as f:
                for line in f:
                    # Skip callbacks/typedefs for now to reduce noise
                    if "typedef" in line:
                        continue
                    match = name_pattern.search(line)
                    if match:
                        func_name = match.group(1)
                        if func_name not in ["main"]: # Exclude main
                            prototypes.append(func_name)
    return set(prototypes)

def count_usages(func_name, srcs_dir):
    count = 0
    # grep -r simple equivalent
    command = f'grep -r "{func_name}" {srcs_dir} | wc -l'
    result = os.popen(command).read().strip()
    try:
        return int(result)
    except:
        return 0

def main():
    header_dir = "includes"
    srcs_dir = "srcs"
    
    print("Scanning headers...")
    funcs = get_function_prototypes(header_dir)
    print(f"Found {len(funcs)} function prototypes.")
    
    print("Checking usages...")
    unused = []
    for func in funcs:
        # We expect at least:
        # 1. The prototype in .h (not counted if we only grep srcs, but let's grep everything or just add 1)
        # Actually, let's grep srcs only.
        # Usage = Definition in .c (1) + Calls (N).
        # So count in srcs should be >= 2 (Definition + at least 1 call).
        # If count == 1, it's likely just defined but never called (or called in the same file? - wait, grep catches same file calls too)
        # BUT: grep matches substring. e.g. "init" matches "init_window".
        # So we need to be careful. usage of `\bname\b` word boundaries is better.
        
        # Using word boundaries for grep
        cmd = f'grep -rE "\\b{func}\\b" {srcs_dir} | wc -l'
        count = int(os.popen(cmd).read().strip())
        
        if count <= 1:
            # If count is 1, it matches the definition itself. So 0 calls.
            # If count is 0, it's not even defined? (Strange if in header)
            unused.append((func, count))
            
    print(f"Potential unused functions ({len(unused)}):")
    
    # Group by file
    file_map = {}
    
    for func, count in unused:
        # Find defining file
        grep_cmd = f'grep -lR "\\b{func}\\b" {srcs_dir}'
        files = os.popen(grep_cmd).read().strip().split('\n')
        defining_file = None
        for f in files:
             if f:
                 defining_file = f
                 break
        
        if defining_file:
            if defining_file not in file_map:
                file_map[defining_file] = []
            file_map[defining_file].append(func)
        else:
            # Header only?
            if "Header Only" not in file_map:
                file_map["Header Only"] = []
            file_map["Header Only"].append(func)

    for fpath, funcs_list in file_map.items():
        print(f"\nFile: {fpath}")
        # Check if file has other functions
        # Count total functions in file (approximation by starting brace at start of line?)
        # Or just read file and simple regex
        if fpath != "Header Only":
             # command to count functions in file
             # ^\w+.*\s+\w+\(
             count_cmd = f'grep -E "^[a-zA-Z_].+\)\s*$" {fpath} | wc -l'
             # This regex is weak but consistent with norminette style (Type\tname(args))
             # Norminette: void\tfoo(args) -> matches ^void
             # Actually norminette often splits return type line? No, usually line break after return type.
             # let's try a simpler heuristic: count unused in list vs total.
             pass
        
        for func in funcs_list:
            print(f"  - {func}")

if __name__ == "__main__":
    main()
