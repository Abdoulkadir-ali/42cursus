# Vecu3 Module

Provides 3D unsigned integer vector helpers. This folder is responsible for non-negative 3-component values where compact unsigned storage is preferable.

---

## Directory Structure
- `srcs/primitives/vectors/vecu3/` — 3D unsigned vectors
- `init.c` — `t_vecu3` constructor
- `arithmetic.c` — In-place unsigned arithmetic
- `distance.c` — Length, min, and max helpers

---

## How It Works

1. `create_vecu3` packs three unsigned integers into a `t_vecu3` value.
2. Arithmetic helpers mutate an existing vector in place.
3. `vecu3_len` computes the Euclidean length and returns it as an unsigned integer.
4. `vecu3_min` and `vecu3_max` expose component bounds.

---

## Developer Notes
- This family mirrors `vecu2` and keeps the same mutation-oriented calling style.

For exported declarations, see `includes/primitives.h`.