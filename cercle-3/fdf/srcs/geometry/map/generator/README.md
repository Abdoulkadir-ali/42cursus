# Geometry Map Generator

## Directory Structure

- `alloc.c`: allocate and free temporary integer heightmaps.
- `init.c`: initialize gradients and permutation tables for noise.
- `interpolate.c`: Perlin fade, lerp, and gradient helpers.
- `noise.c`: sample 2D Perlin noise.
- `octave.c`: layer multiple noise octaves into one normalized value.
- `builder.c`: fill a heightmap from the configured noise parameters.
- `generator.c`: convert a heightmap into a styled `t_map`.
- `writer.c`: optional file export for generated heightmaps.
- `atof.c`: small parsing helpers for generator arguments.
- `main.c`: archived standalone generator entry point.

## How It Works

The generator builds procedural terrain from seeded Perlin noise. It initializes a
noise state, samples several octaves across the target grid, scales the result
into integer heights, then converts that height array into the same `t_map`
structure used by loaded maps.

## Developer Notes

- Runtime generation and file-based maps share the same styling and min/max pass.
- `main.c` is kept as a commented standalone utility reference rather than part of
  the normal build.