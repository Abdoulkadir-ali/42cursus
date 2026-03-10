# Geometry Tesselation

## Directory Structure

- `tesselation.c`: single-pass mesh densification entry point.
- `helper.c`: allocate and finalize the denser destination map.
- `compute.c`: dispatch each destination cell to the right interpolation mode.
- `direct.c`: copy source vertices that land on even grid positions.
- `horizontal.c`: interpolate points between horizontal neighbors.
- `vertical.c`: interpolate points between vertical neighbors.
- `diagonal.c`: interpolate center cells from both diagonals.
- `utils.c`: shared position and color interpolation helpers.
- `manager.c`: apply multiple tessellation levels in sequence.
- `submap.c`: extract a bounded region before tessellating it.

## How It Works

Tessellation doubles grid density minus shared borders. Existing source vertices
are copied into even coordinates, while odd coordinates are created by linear
interpolation between neighboring points and colors. Higher tessellation levels
repeat the same operation on the newly generated map.

## Global Pipeline

1. Allocate a destination map sized to `(2w - 1, 2h - 1)`.
2. Visit every destination point.
3. Choose direct, horizontal, vertical, or diagonal interpolation.
4. Preserve raw positions, display colors, and source colors together.
5. Optionally repeat the pass or apply it to a submap.

## Developer Notes

- Boundary cells fall back to direct copies when a neighbor is missing.
- Submap extraction lets the renderer densify only a focused region when needed.