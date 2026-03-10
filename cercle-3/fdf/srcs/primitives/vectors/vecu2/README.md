# Vecu2 Module

Provides 2D unsigned integer vector helpers. This folder is responsible for small non-negative counts, dimensions, and component-wise unsigned arithmetic.

---

## Directory Structure
- `srcs/primitives/vectors/vecu2/` — 2D unsigned vectors
- `init.c` — `t_vecu2` constructor
- `arithmetic.c` — In-place unsigned arithmetic
- `distance.c` — Length, min, and max helpers

---

## How It Works

1. `create_vecu2` packs two unsigned integers into a `t_vecu2` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vecu2_len` computes the Euclidean length and returns it as an unsigned integer.
4. `vecu2_min` and `vecu2_max` expose component bounds.

---

## Developer Notes
- This family assumes callers already manage underflow semantics before subtraction where needed.

For exported declarations, see `includes/primitives.h`.