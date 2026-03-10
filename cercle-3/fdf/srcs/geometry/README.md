# Geometry Module

## Directory Structure

- `color/`: RGB helpers, interpolation, and height-based palette logic.
- `map/`: map loading, parsing, synthetic generation, styling, and storage.
- `tesselation/`: mesh densification helpers used to create denser map grids.

## How It Works

The geometry module owns the application's terrain data. It turns `.fdf` files or
generated noise fields into `t_map` instances, computes metadata such as minimum
and maximum altitude, applies visual styles to each point, and provides optional
tessellation helpers for denser render inputs.

Imported maps follow a read pipeline: enumerate files, load them into memory,
parse height and optional color tokens, then finalize the resulting `t_map` so
the renderer receives populated positions, colors, and range information.

Generated maps follow a parallel path: a seeded noise state produces an integer
heightmap, that heightmap is converted into a `t_map`, and the same style and
range metadata are applied before the map is exposed to the rest of the engine.

## Global Pipeline

1. `init_map_list()` discovers available `.fdf` files or falls back to a test grid.
2. `load_map()` or `generate_runtime_map()` builds a `t_map` instance.
3. Build helpers compute altitude ranges and the z divisor.
4. Style helpers derive display colors from source values or theme rules.
5. Optional tessellation creates denser copies or focused submaps for rendering.

## Developer Notes

- `points.raw` stores source-space geometry, while `points.pos` mirrors the active
  geometry buffer used downstream by the renderer.
- `points.source_color` preserves original per-point colors so style changes can be
  reapplied without losing imported color data.
- Tessellation keeps source colors and interpolated display colors in sync so the
  render module can swap between base and dense maps safely.