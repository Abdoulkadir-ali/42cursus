# Geometry Map

## Directory Structure

- `build/`: allocate or synthesize map grids and compute range metadata.
- `generator/`: produce runtime-generated maps from seeded noise.
- `read/`: discover, load, parse, and cycle `.fdf` files.
- `style/`: apply visual themes to map points.
- `generate.c`: swap the current map with a newly generated terrain.

## How It Works

The map layer is responsible for creating and managing `t_map` instances. It can
load maps from disk, build a fallback synthetic grid, or generate procedural
terrain at runtime. Once the raw point data exists, build helpers compute height
ranges and style helpers assign display colors.

## Global Pipeline

1. Discover files with `init_map_list()`.
2. Load or generate a `t_map`.
3. Compute `min_max_z`, projected range, and `z_divisor`.
4. Apply the active style to every point.
5. Expose the map through `t_maps.current_map`.

## Developer Notes

- Imported and generated maps converge on the same `t_map` layout.
- Runtime generation increments `generated_id` so repeated generations change seed.