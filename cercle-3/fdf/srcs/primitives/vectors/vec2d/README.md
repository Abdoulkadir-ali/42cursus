# Vec2d Module

Provides 2D double-precision vector helpers. This folder is responsible for fractional positions and distances where integer truncation would be too coarse.

---

## Directory Structure
- `srcs/primitives/vectors/vec2d/` — 2D double vectors
- `init.c` — `t_vec2d` constructor
- `arithmetic.c` — In-place double arithmetic
- `distance.c` — Length, min, max, and min-max helpers

---

## How It Works

1. `create_vec2d` packs two doubles into a `t_vec2d` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vec2d_len` computes the Euclidean length in double precision.
4. `vec2d_min`, `vec2d_max`, and `vec2d_minmax` summarize component bounds.

---

## Developer Notes
- This family mirrors `vec2` closely so higher-level code can switch precision without changing calling style.

For exported declarations, see `includes/primitives.h`.