# Vec3 Module

Provides 3D integer vector helpers. This folder is responsible for integer 3-component values such as RGB colors and compact grid-aligned positions.

---

## Directory Structure
- `srcs/primitives/vectors/vec3/` — 3D integer vectors
- `init.c` — `t_vec3` constructor
- `arithmetic.c` — In-place integer arithmetic
- `distance.c` — Length, min, max, and component-range helpers

---

## How It Works

1. `create_vec3` packs three integers into a `t_vec3` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vec3_len` computes the Euclidean length.
4. `vec3_min`, `vec3_max`, and `vec3_get_minmax_components` expose the component range.

---

## Developer Notes
- Returning the min/max pair as `t_vec2` keeps the API compact when only the bounds are needed.

For exported declarations, see `includes/primitives.h`.