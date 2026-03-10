# Vector Families

Provides the typed vector helpers used across geometry, rendering, GUI layout, and map processing. This folder is responsible for grouping the vector API by dimensionality and numeric representation.

---

## Directory Structure
- `srcs/primitives/vectors/` — Vector family root
- `vec2/` — 2D integer vectors
- `vec2d/` — 2D double vectors
- `vec3/` — 3D integer vectors
- `vec3d/` — 3D double vectors
- `vecu2/` — 2D unsigned integer vectors
- `vecu3/` — 3D unsigned integer vectors

---

## How It Works

1. Each family exposes a constructor in `init.c`.
2. `arithmetic.c` provides in-place add, subtract, multiply, divide, and scalar-multiply operations.
3. `distance.c` provides length and min-max helpers adapted to that type.
4. Higher-level modules choose the vector family that matches their precision and storage needs.

---

## Developer Notes
- The APIs are intentionally parallel across families to make cross-type use predictable.
- Divide helpers skip components whose divisor is zero instead of forcing an error path.

For exported declarations, see `includes/primitives.h`.