# Vec2 Module

Provides 2D integer vector helpers. This folder is responsible for screen-space integer positions, simple component-wise arithmetic, and short integer distance and bounds helpers.

---

## Directory Structure
- `srcs/primitives/vectors/vec2/` — 2D integer vectors
- `init.c` — `t_vec2` constructor
- `arithmetic.c` — In-place integer arithmetic
- `distance.c` — Length, min, max, and min-max helpers

---

## How It Works

1. `create_vec2` packs two integers into a `t_vec2` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vec2_len` computes an integer Euclidean length.
4. `vec2_min`, `vec2_max`, and `vec2_minmax` summarize component bounds.

---

## Developer Notes
- This family is used where integer pixel or grid coordinates are more appropriate than floating-point values.

For exported declarations, see `includes/primitives.h`.