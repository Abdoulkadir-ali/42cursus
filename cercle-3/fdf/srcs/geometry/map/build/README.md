# Geometry Map Build

## Directory Structure

- `grid.c`: create and free synthetic grid maps.
- `helper.c`: initialize grid points, compute z scaling, and allocate arrays.
- `minmax.c`: scan the map to compute altitude bounds.

## How It Works

Build helpers prepare `t_map` buffers once dimensions are known. They support the
fallback test grid, initialize per-point coordinates, and compute the metadata
used later by the renderer and GUI.

## Developer Notes

- The test grid provides a safe fallback whenever loading fails.
- `z_divisor` compresses large altitude ranges into a manageable display scale.