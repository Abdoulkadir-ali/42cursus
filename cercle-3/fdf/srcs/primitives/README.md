# Primitives Module

Provides the small math and utility building blocks used throughout the project. This subtree is responsible for vector construction, in-place vector arithmetic, simple distance and min-max helpers, matrix construction, and scalar clamping.

---

## Directory Structure
- `srcs/primitives/` — Primitive math helpers
- `clamp.c` — Scalar and color clamping utilities
- `matrix/` — 4x4 matrix constructors and multiplication
- `vectors/` — Typed vector families for integer, double, and unsigned values

---

## How It Works

### Global Pipeline
1. Higher-level systems allocate points, positions, offsets, and colors with the vector constructors.
2. In-place arithmetic helpers update those values without heap allocation.
3. Distance and min-max helpers extract simple geometric facts used by camera, map, render, and GUI code.
4. Matrix helpers build identity, translation, and scale matrices, then compose them through multiplication.
5. Clamp helpers bound raw values before they propagate into rendering or input state.

---

## Developer Notes
- The vector API is intentionally small and mutation-oriented.
- Most helpers are typed by storage class rather than abstracted through macros.
- Matrix utilities here focus on the small subset needed by the render pipeline.

For exported declarations, see `includes/primitives.h`.