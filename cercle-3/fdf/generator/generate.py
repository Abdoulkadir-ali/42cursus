#!/usr/bin/env python3
import argparse
import concurrent.futures
import math
import os
import random
import sys
import uuid

DEFAULT_OUTPUT_DIR = "./maps/generated_maps"
IMAGE_EXTENSIONS = (".jpg", ".jpeg", ".png", ".bmp", ".tiff", ".gif")

try:
    from PIL import Image
    PIL_AVAILABLE = True
except ImportError:
    PIL_AVAILABLE = False


def fail(message):
    print(message)
    sys.exit(1)


class PerlinNoise:
    def __init__(self, seed=None):
        if seed is not None:
            random.seed(seed)
        self.perm = list(range(256))
        random.shuffle(self.perm)
        self.perm += self.perm
        self.dirs = [
            (math.cos(angle * 2.0 * math.pi / 256),
             math.sin(angle * 2.0 * math.pi / 256))
            for angle in range(256)
        ]

    def noise(self, x, y):
        def surflet(grid_x, grid_y):
            dist_x = abs(x - grid_x)
            dist_y = abs(y - grid_y)
            poly_x = 1 - 6 * dist_x ** 5 + 15 * dist_x ** 4 - 10 * dist_x ** 3
            poly_y = 1 - 6 * dist_y ** 5 + 15 * dist_y ** 4 - 10 * dist_y ** 3
            hashed = self.perm[
                self.perm[int(grid_x) % 256] + int(grid_y) % 256
            ]
            grad = self.dirs[hashed]
            return poly_x * poly_y * (grad[0] * dist_x + grad[1] * dist_y)

        int_x = int(x)
        int_y = int(y)
        return (
            surflet(int_x, int_y)
            + surflet(int_x + 1, int_y)
            + surflet(int_x, int_y + 1)
            + surflet(int_x + 1, int_y + 1)
        )


class MapGenerator:
    def __init__(self, folder_path=DEFAULT_OUTPUT_DIR):
        self.folder_path = folder_path
        self._ensure_folder_exists()
        self.noise_gen = PerlinNoise()

    def _ensure_folder_exists(self):
        try:
            os.makedirs(self.folder_path, exist_ok=True)
        except OSError as error:
            fail(f"Error creating directory {self.folder_path}: {error}")

    def _noise_value(self, x, y, width, height, scale, octaves, persistence):
        total = 0
        frequency = 1
        amplitude = 1
        max_value = 0

        for _ in range(octaves):
            sample_x = x / width * scale * frequency
            sample_y = y / height * scale * frequency
            total += self.noise_gen.noise(sample_x, sample_y) * amplitude
            max_value += amplitude
            amplitude *= persistence
            frequency *= 2
        return (total / max_value) + 0.5

    def _compute_row(self, y, width, height, scale, z_scale, octaves,
                     persistence):
        row = []
        for x in range(width):
            value = self._noise_value(x, y, width, height, scale, octaves,
                                      persistence)
            row.append(int(value * z_scale))
        return y, row

    def generate_noise_map(self, width, height, scale=4.0, z_scale=10.0,
                           octaves=2, persistence=0.5):
        print(f"Generating noise map {width}x{height} with z-scale {z_scale}...")
        data = [None] * height

        with concurrent.futures.ThreadPoolExecutor() as executor:
            futures = [
                executor.submit(
                    self._compute_row,
                    y,
                    width,
                    height,
                    scale,
                    z_scale,
                    octaves,
                    persistence,
                )
                for y in range(height)
            ]
            for future in concurrent.futures.as_completed(futures):
                y, row = future.result()
                data[y] = row
        return data

    def _require_pillow(self):
        if not PIL_AVAILABLE:
            fail(
                "Error: PIL (Pillow) library is required for image mode.\n"
                "Install it with: pip install Pillow"
            )

    def _validate_image_path(self, image_path):
        if not image_path or not os.path.exists(image_path):
            fail(f"Error: Image file '{image_path}' not found.")

    def _resize_dimensions(self, orig_w, orig_h, width, height):
        aspect = orig_w / orig_h
        if width / height > aspect:
            return int(height * aspect), height
        return width, int(width / aspect)

    def generate_image_map(self, image_path, width, height, z_scale):
        self._require_pillow()
        self._validate_image_path(image_path)

        try:
            print(f"Loading image '{image_path}'...")
            with Image.open(image_path) as source:
                img = source.convert("RGB")
            orig_w, orig_h = img.size
            new_w, new_h = self._resize_dimensions(orig_w, orig_h,
                                                   width, height)
            img = img.resize((new_w, new_h), Image.LANCZOS)
            print(f"Resizing to {new_w}x{new_h} (aspect ratio preserved)...")
            data = [[(0, "0xFFFFFF") for _ in range(new_w)]
                    for _ in range(new_h)]
            pixels = img.load()
            for y in range(new_h):
                for x in range(new_w):
                    r, g, b = pixels[x, y]
                    luminance = 0.299 * r + 0.587 * g + 0.114 * b
                    height_val = int((luminance / 255.0) * z_scale)
                    hex_color = f"0x{r:02X}{g:02X}{b:02X}"
                    data[y][x] = (height_val, hex_color)
            return data
        except Exception as error:
            fail(f"Error processing image: {error}")

    def generate_flat_map(self, width, height):
        return [[0 for _ in range(width)] for _ in range(height)]

    def _resolve_output_path(self, filename):
        if os.path.dirname(filename):
            full_path = filename
        else:
            full_path = os.path.join(self.folder_path, filename)
        if not full_path.endswith(".fdf"):
            full_path += ".fdf"
        return full_path

    def _format_item(self, item):
        if isinstance(item, tuple):
            return f"{item[0]},{item[1]}"
        return str(item)

    def save_map(self, data, filename):
        full_path = self._resolve_output_path(filename)
        print(f"Saving to '{full_path}'...")
        try:
            with open(full_path, "w") as file:
                for row in data:
                    line = " ".join(self._format_item(item) for item in row)
                    file.write(line + "\n")
            print("Done!")
            return full_path
        except IOError as error:
            fail(f"Error saving file: {error}")

    def _iter_image_files(self, image_path):
        if not os.path.isdir(image_path):
            return [image_path]

        image_files = []
        for entry in sorted(os.listdir(image_path)):
            full_path = os.path.join(image_path, entry)
            if os.path.isfile(full_path) and entry.lower().endswith(
                IMAGE_EXTENSIONS
            ):
                image_files.append(full_path)
        return image_files

    def process_images(self, image_path, width, height, z_scale):
        self._validate_image_path(image_path)
        image_files = self._iter_image_files(image_path)
        if not image_files:
            print(f"No image files found in directory '{image_path}'.")
            return

        for img_path in image_files:
            name = os.path.splitext(os.path.basename(img_path))[0]
            print(f"Processing {img_path}...")
            data = self.generate_image_map(img_path, width, height, z_scale)
            self.save_map(data, name)


def build_parser():
    parser = argparse.ArgumentParser(
        description="Generate FDF maps from noise, flat grids, or images."
    )
    parser.add_argument(
        "name",
        nargs="?",
        default=None,
        help=(
            "Output filename (saved to ./maps/generated_maps by default, "
            "or auto-generated when omitted)"
        ),
    )
    parser.add_argument("--width", "-w", type=int, default=1000,
                        help="Map width")
    parser.add_argument("--height", "-H", type=int, default=1000,
                        help="Map height")
    parser.add_argument("--scale", "-z", type=float, default=10000.0,
                        help="Z-axis scale / height multiplier")
    parser.add_argument("--mode", "-m", choices=["noise", "image", "flat"],
                        default="noise", help="Generation mode")
    parser.add_argument("--image", "-i", type=str,
                        help="Input image path (required for image mode)")
    parser.add_argument("--folder", "-f", type=str,
                        default=DEFAULT_OUTPUT_DIR,
                        help="Default output folder")
    return parser


def generate_named_map(args, generator):
    output_name = args.name or f"generated_{uuid.uuid4().hex[:8]}"
    if args.mode == "noise":
        data = generator.generate_noise_map(
            args.width,
            args.height,
            z_scale=args.scale,
        )
    else:
        data = generator.generate_flat_map(args.width, args.height)
    generator.save_map(data, output_name)


def main():
    parser = build_parser()
    args = parser.parse_args()

    if args.width <= 0 or args.height <= 0:
        parser.error("--width and --height must be greater than 0")
    if args.mode == "image" and not args.image:
        parser.error("--image is required when --mode image is used")

    generator = MapGenerator(folder_path=args.folder)
    if args.mode == "image":
        generator.process_images(args.image, args.width, args.height,
                                 args.scale)
    else:
        generate_named_map(args, generator)
    return 0


if __name__ == "__main__":
    sys.exit(main())
