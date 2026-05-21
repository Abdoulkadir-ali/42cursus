# miniRT — high-performance CPU ray tracer

A 42-style miniRT that scales to **millions of primitives** on CPU thanks to a
SAH-built BVH, multi-threaded tile rendering and cache-friendly data layout.

## Benchmarks (this machine, 12 logical cores, 1280×720)

| Scene                | Primitives | Render time | Wall (incl. parse + BVH) |
|----------------------|-----------:|------------:|-------------------------:|
| `scenes/basic.rt`    |         11 |   ~14 ms    | ~30 ms                   |
| `scenes/stress_1M.rt`|  1 000 000 |  ~348 ms    | ~1.24 s                  |

## Build

```
make
```

Requires `libX11`, `libXext` (already linked from `packages/minilibx-linux`).

## Run

```
./miniRT scenes/basic.rt
```

ESC or window-close exits cleanly.

### Headless / benchmark mode (no X server, dumps PPM)

```
MINIRT_HEADLESS=1 MINIRT_OUT=out.ppm ./miniRT scenes/basic.rt
```

### Generate a stress scene

```
python3 scripts/gen_stress.py 1000000 scenes/stress_1M.rt
MINIRT_HEADLESS=1 MINIRT_OUT=out.ppm ./miniRT scenes/stress_1M.rt
```

## .rt file format (subject-compliant)

```
A  <ratio 0..1> <r,g,b>                     # ambient (one allowed)
C  <x,y,z> <nx,ny,nz>  <fov 0..180>          # camera (one allowed)
L  <x,y,z> <ratio 0..1> [r,g,b]              # point light (multiple)

sp <x,y,z> <diameter>           <r,g,b>
pl <x,y,z> <nx,ny,nz>           <r,g,b>
cy <x,y,z> <nx,ny,nz> <diam> <h> <r,g,b>
```

Lines beginning with `#` are comments; blank lines are ignored.

## Why it's fast

- **SAH-binned BVH** with 16 bins → O(log N) ray traversal even at 1 M objects.
- **Iterative traversal** with explicit 64-deep stack + branchless slab AABB test
  (no recursion, no virtual dispatch).
- **Tile-based work-stealing pool** (32×32 tiles, mutex-guarded queue) saturates
  all logical cores (~400 % CPU on 12 threads).
- **Compact 32-byte BVH nodes** (2 per cache line); single-precision storage.
- **Planes kept outside the BVH** (they have no finite bounds) and tested in a
  separate flat list, so the BVH stays tight.
- **Shadow rays use the same BVH** with early-out `bvh_occluded`.
- `-O3 -ffast-math -march=native -funroll-loops` for autovectorization.

## File layout

```
include/        public headers (minirt.h, vec3.h, scene.h, bvh.h)
src/math/       vec3 inlines, AABB, numeric utils
src/primitives/ sphere/plane/cylinder hit + bounds
src/bvh/        SAH builder + traversal + occlusion
src/scene/      scene + camera setup
src/parser/     .rt tokenizer + per-keyword parsers
src/render/     primary-ray gen, shading, threading
src/mlx/        window, key/close hooks
src/utils/      error + cleanup
scenes/         sample .rt files
scripts/        stress-scene generator
packages/minilibx-linux/  bundled MiniLibX
```

## Subject compliance

- Required objects: sphere, plane, cylinder ✔
- Ambient + point light(s) ✔
- Hard shadows ✔
- `.rt` parser with strict validation, must end in `.rt` ✔
- Camera with FOV ∈ (0,180) ✔
- ESC + window-close exit cleanly ✔
- `Error\n` then descriptive message on any parse/runtime failure ✔
- No leaks in steady state (everything freed in `app_cleanup`).

## Notes

- Window size is fixed (`WIN_W`/`WIN_H` in `include/minirt.h`).
- For interactive resize / camera movement, set `app->dirty = 1` from a key
  hook — the loop will re-render that frame.
