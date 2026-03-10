# Matrix Module

Provides the small 4x4 matrix helpers used by the renderer. This folder is responsible for creating identity, translation, and scale matrices and for multiplying matrices when transforms need to be composed.

---

## Directory Structure
- `srcs/primitives/matrix/` — Matrix helpers
- `matrix.c` — Identity, multiplication, translation, and scale constructors

---

## How It Works

1. `matrix_identity` clears a `t_matrix4` and seeds the diagonal with `1.0f`.
2. `matrix_translation` starts from the identity matrix and places translation values in the last column.
3. `matrix_scale` starts from the identity matrix and replaces the diagonal scale terms.
4. `matrix_multiply` performs the standard triple-loop 4x4 composition.

---

## Developer Notes
- Matrices are value types, so helpers return a fully built `t_matrix4` by value.
- The implementation keeps composition explicit rather than hiding it behind macros or dynamic allocation.

For exported declarations, see `includes/primitives.h`.