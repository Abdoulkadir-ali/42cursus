#!/usr/bin/env python3
import argparse
import random
import math
import sys
import os
import concurrent.futures
import uuid

try:
    from PIL import Image
    PIL_AVAILABLE = True
except ImportError:
    PIL_AVAILABLE = False

class PerlinNoise:
    def __init__(self, seed=None):
        if seed:
            random.seed(seed)
        self.perm = list(range(256))
        random.shuffle(self.perm)
        self.perm += self.perm
        self.dirs = [(math.cos(a * 2.0 * math.pi / 256),
                      math.sin(a * 2.0 * math.pi / 256))
                     for a in range(256)]

    def noise(self, x, y):
        def surflet(grid_x, grid_y):
            dist_x, dist_y = abs(x - grid_x), abs(y - grid_y)
            poly_x = 1 - 6 * dist_x ** 5 + 15 * dist_x ** 4 - 10 * dist_x ** 3
            poly_y = 1 - 6 * dist_y ** 5 + 15 * dist_y ** 4 - 10 * dist_y ** 3
            hashed = self.perm[self.perm[int(grid_x) % 256] + int(grid_y) % 256]
            grad = self.dirs[hashed]
            return poly_x * poly_y * (grad[0] * dist_x + grad[1] * dist_y)

        int_x, int_y = int(x), int(y)
        return (surflet(int_x, int_y) + surflet(int_x + 1, int_y) +
                surflet(int_x, int_y + 1) + surflet(int_x + 1, int_y + 1))

class MapGenerator:
    def __init__(self, folder_path="maps/test_maps"):
        self.folder_path = folder_path
        self._ensure_folder_exists()
        self.noise_gen = PerlinNoise()

    def _ensure_folder_exists(self):
        if not os.path.exists(self.folder_path):
            try:
                os.makedirs(self.folder_path)
                print(f"Created directory: {self.folder_path}")
            except OSError as e:
                print(f"Error creating directory {self.folder_path}: {e}")
                sys.exit(1)

    def _compute_row(self, y, width, height, scale, z_scale, octaves, persistence):
        row = []
        for x in range(width):
            total = 0
            frequency = 1
            amplitude = 1
            max_value = 0
            for _ in range(octaves):
                total += self.noise_gen.noise(x / width * scale * frequency,
                                              y / height * scale * frequency) * amplitude
                max_value += amplitude
                amplitude *= persistence
                frequency *= 2
            val = (total / max_value) + 0.5
            row.append(int(val * z_scale))
        return y, row

    def generate_noise_map(self, width, height, scale=4.0, z_scale=10.0, octaves=2, persistence=0.5):
        print(f"Generating noise map {width}x{height} with z-scale {z_scale}...")
        data = [None] * height
        
        with concurrent.futures.ThreadPoolExecutor() as executor:
            futures = [executor.submit(self._compute_row, y, width, height, scale, z_scale, octaves, persistence) for y in range(height)]
            for future in concurrent.futures.as_completed(futures):
                y, row = future.result()
                data[y] = row
        return data

    def generate_image_map(self, image_path, width, height, z_scale):
        if not PIL_AVAILABLE:
            print("Error: PIL (Pillow) library is required for image mode.")
            print("Install it with: pip install Pillow")
            sys.exit(1)
        
        if not os.path.exists(image_path):
            print(f"Error: Image file '{image_path}' not found.")
            sys.exit(1)

        try:
            print(f"Loading image '{image_path}'...")
            img = Image.open(image_path).convert('RGB')
            img = img.transpose(Image.FLIP_TOP_BOTTOM)  # Flip to correct orientation
            orig_w, orig_h = img.size
            aspect = orig_w / orig_h
            
            if width / height > aspect:
                new_w = int(height * aspect)
                new_h = height
            else:
                new_w = width
                new_h = int(width / aspect)
            
            img = img.resize((new_w, new_h), Image.Resampling.LANCZOS)
            print(f"Resizing to {new_w}x{new_h} (aspect ratio preserved)...")
            
            data = [[(0, "0xFFFFFF") for _ in range(new_w)] for _ in range(new_h)]
            pixels = img.load()
            
            for y in range(new_h):
                for x in range(new_w):
                    r, g, b = pixels[x, y]
                    # Luminance for height
                    lum = 0.299 * r + 0.587 * g + 0.114 * b
                    val = lum / 255.0
                    height_val = int(val * z_scale)
                    
                    # RGB to Hex String
                    hex_color = "0x{:02X}{:02X}{:02X}".format(r, g, b)
                    data[y][x] = (height_val, hex_color)
            
            return data
        except Exception as e:
            print(f"Error processing image: {e}")
            sys.exit(1)

    def generate_flat_map(self, width, height):
        return [[0 for _ in range(width)] for _ in range(height)]

    def save_map(self, data, filename):
        if os.path.dirname(filename):
            full_path = filename
        else:
            full_path = os.path.join(self.folder_path, filename)

        # Ensure extension
        if not full_path.endswith('.fdf'):
            full_path += '.fdf'

        print(f"Saving to '{full_path}'...")
        try:
            with open(full_path, 'w') as f:
                for row in data:
                    line_parts = []
                    for item in row:
                        if isinstance(item, tuple):
                             # (height, color_hex)
                             line_parts.append(f"{item[0]},{item[1]}")
                        else:
                             # Just height
                             line_parts.append(str(item))
                    line = " ".join(line_parts)
                    f.write(line + "\n")
            print("Done!")
            return full_path
        except IOError as e:
            print(f"Error saving file: {e}")
            sys.exit(1)

    def process_images(self, image_path, width, height, z_scale):
        if os.path.isdir(image_path):
            # Process all image files in the directory
            import glob
            image_extensions = ["*.jpg", "*.jpeg", "*.png", "*.bmp", "*.tiff", "*.gif"]
            image_files = []
            for ext in image_extensions:
                image_files.extend(glob.glob(os.path.join(image_path, ext)))
            if not image_files:
                print(f"No image files found in directory '{image_path}'.")
                return
            for img_path in image_files:
                base = os.path.basename(img_path)
                name = os.path.splitext(base)[0]
                print(f"Processing {img_path}...")
                data = self.generate_image_map(img_path, width, height, z_scale)
                self.save_map(data, name)
        else:
            # Single image
            if not os.path.exists(image_path):
                print(f"Error: Image file '{image_path}' not found.")
                return
            base = os.path.basename(image_path)
            name = os.path.splitext(base)[0]
            data = self.generate_image_map(image_path, width, height, z_scale)
            self.save_map(data, name)


def main():
    folder_path = "../maps/test_maps"
    parser = argparse.ArgumentParser(description="Generate FDF maps from noise or images.")
    parser.add_argument("name", nargs='?', default=None, help=f"Output filename (saved to {folder_path} by default, generates unique name if not provided)")
    parser.add_argument("--width", "-w", type=int, default=1000, help="Map width")
    parser.add_argument("--height", "-H", type=int, default=1000, help="Map height")
    parser.add_argument("--scale", "-z", type=float, default=10000.0, help="Z-axis scale/height multiplier")
    parser.add_argument("--mode", "-m", choices=["noise", "image", "flat"], default="noise", help="Generation mode")
    parser.add_argument("--image", "-i", type=str, help="Input image path (required for image mode)")
    parser.add_argument("--folder", "-f", type=str, default=folder_path, help="Default output folder")

    args = parser.parse_args()

    generator = MapGenerator(folder_path=args.folder)

    if args.mode == "image":
        generator.process_images(args.image, args.width, args.height, args.scale)
    else:
        if not args.name:
            args.name = f"generated_{uuid.uuid4().hex[:8]}"

        if args.mode == "noise":
            data = generator.generate_noise_map(args.width, args.height, z_scale=args.scale)
        elif args.mode == "flat":
            data = generator.generate_flat_map(args.width, args.height)
        else:
            print("Invalid mode.")
            sys.exit(1)

        generator.save_map(data, args.name)


if __name__ == "__main__":
    main()
