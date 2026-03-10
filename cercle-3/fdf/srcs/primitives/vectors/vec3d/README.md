# Vec3d Module

Provides 3D double-precision vector helpers. This folder is responsible for fractional spatial values used in the render and camera math.

---

## Directory Structure
- `srcs/primitives/vectors/vec3d/` — 3D double vectors
- `init.c` — `t_vec3d` constructor
- `arithmetic.c` — In-place double arithmetic
- `distance.c` — Length, min, max, and component-range helpers

---

## How It Works

1. `create_vec3d` packs three doubles into a `t_vec3d` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vec3d_len` computes the Euclidean length in double precision.
4. `vec3d_min`, `vec3d_max`, and `vec3d_minmax` expose the component range.

---

## Developer Notes
- This family is the floating-point companion to `vec3` and keeps the same function shape wherever possible.

For exported declarations, see `includes/primitives.h`.