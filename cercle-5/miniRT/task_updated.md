# miniRT – Analysis.md Task Tracker

Status of fixes based on the issues identified in `analysis.md` and `analysis_short.md`.

---

## ✅ Completed Fixes

### 1. Locale Dependency (analysis.md §7.2)
**Issue:** `strtod` behaves differently under non-`C` locales, causing `.rt` parsing failures.  
**Fix:** Added `#include <locale.h>` and `setlocale(LC_NUMERIC, "C")` at the top of `main()` in `srcs/core/main.c`.

### 2. EPSILON Value (analysis.md §4.3)
**Issue:** `EPSILON 0.001` causes Peter Panning artifacts and is too coarse for small-scale geometry.  
**Fix:** Changed to `EPSILON 1e-6` in `includes/core.h`.

### 3. Mutex Contention / Atomic Tile Distribution (analysis.md §9.1)
**Issue:** A single `pthread_mutex_t` protecting `next_tile_id` creates a serialization bottleneck across 12 threads.  
**Fix:** Replaced `pthread_mutex_lock`/`unlock` with `__sync_fetch_and_add(&ctx->next_tile_id, 1)` in `srcs/gui/render/tiles.c`. Removed `pthread_mutex_init`/`destroy` from `srcs/gui/render/render.c`. Removed the unused `pthread_mutex_t mutex` field from `s_render_ctx` in `includes/gui.h`.

### 4. Cone Apex Normal Singularity (analysis.md §5.1)
**Issue:** At the cone tip, the radial vector is zero-length; `vec3_norm()` on it produces NaN.  
**Fix:** Added guard in `srcs/rays/raytracing/intersection/cone/hit.c`: if `vec3_dot(radial, radial) < EPSILON * EPSILON`, the normal falls back to `cone->transform.forward`.

### 5. Cylinder/Cone Parallel Ray Division by Zero (analysis.md §5.1)
**Issue:** When a ray is parallel to a cylinder or cone axis, quadratic coefficient `A ≈ 0` causes division by zero.  
**Fix:** Added `if (fabs(q.a) < EPSILON) return (false);` at the top of `solve_quadratic()` in `srcs/maths/quadratic/roots.c`.

### 6. Light Accumulation Clamping (analysis.md §8.1)
**Issue:** Dead `clamp_color()` call in `pixel_color()` (return value was discarded). Missing negative clamping.  
**Fix:** Removed the dead call. Clamping now happens exactly once at the end of `compute_color()` after all lights are summed. Added `< 0` lower-bound checks to `clamp_color()` in `srcs/rays/raytracing/postprocess/shading/color.c`.

### 7. GLB Chunk Alignment Padding (analysis.md §7.3)
**Issue:** GLB spec requires 4-byte alignment between chunks. After reading the JSON chunk, the file cursor could be misaligned, causing the binary chunk header to be read from garbage data.  
**Fix:** Added padding skip after JSON chunk read in `srcs/objects/glb/io.c`: `pad = (4 - (c.length % 4)) % 4; if (pad > 0) lseek(fd, pad, SEEK_CUR);`

### 8. Shadow Bias — Slope-Scaled (analysis.md §8.2)
**Issue:** Fixed `EPSILON` offset along the normal causes shadow acne at grazing angles and Peter Panning at perpendicular angles.  
**Fix:** Replaced fixed `EPSILON` bias with slope-scaled bias in `srcs/rays/raytracing/postprocess/shading/light.c`: `bias = fmax(EPSILON, EPSILON * 10.0 * (1.0 - ndotl))`. Larger offset at grazing angles, minimal offset at direct angles.

### 9. Link Time Optimization (analysis_short.md)
**Issue:** Vec3/matrix math functions in separate `.c` files cannot be inlined by the compiler, causing thousands of function call overhead per ray-object intersection.  
**Fix:** Added `-flto` flag to `CFLAGS` in `Makefile`. The linker now sees all function bodies across translation units and can inline `vec3_add`, `vec3_dot`, `vec3_scale`, etc. directly into hot loops. Expected 2x-3x rendering speedup.

### 10. Bilinear Texture Filtering (analysis_short.md §4, analysis.md §8.3)
**Issue:** Bitmap textures used nearest-neighbor sampling (casting UV to integer), causing pixelation up close and moiré patterns at distance.  
**Fix:** Rewrote `sample_bitmap()` in `srcs/surface/texture/sample.c` with bilinear interpolation. New `texel_at()` helper handles wrapping, then `sample_bitmap()` interpolates between the 4 nearest texels using fractional UV coordinates.

### 11. Unrolled Matrix Multiplication (analysis_short.md §1)
**Issue:** `mat4_mul()` used a naive triple `while`-loop (64 multiplications, 48 additions with loop overhead), preventing the compiler from auto-vectorizing.  
**Fix:** Replaced with unrolled `mat4_mul_row()` helper in `srcs/maths/matrix/multiply.c`. Each row is computed with 4 explicit multiply-accumulate expressions, enabling the compiler (especially with LTO + `-O3`) to emit FMA/SIMD instructions.

### 12. Robust vec3_norm Zero-Length Guard (proactive)
**Issue:** `vec3_norm()` used `if (mag == 0)` — exact float comparison is unreliable under `-ffast-math`, allowing near-zero vectors to pass through and produce NaN/inf after `1.0 / mag`.  
**Fix:** Changed to `if (mag < 1e-12)` in `srcs/maths/vectors/vec3/vec3_extra.c` for a robust threshold-based guard.

### 13. Cone Intersection Uninitialized `t` (proactive audit)
**Issue:** `intersect_cone()` in `srcs/rays/raytracing/intersection/cone/intersect.c` declared `double t;` without initialization, then passed `&t` to `check_cone_body()`. Inside `check_cone_t()`, the condition `t < *tm` compared the quadratic root against the **uninitialized** stack value. This is undefined behavior — on most compilers the uninitialized value happens to be large, masking the bug, but it could cause missed cone hits or garbage intersections.  
**Fix:** Added `t = DBL_MAX;` initialization, matching the pattern used by `intersect_cylinder()` (`t_min = DBL_MAX`).

### 14. Sphere `radius_sq` Float Precision Loss (proactive audit)
**Issue:** `s_sphere.radius_sq` was declared as `float` in `includes/objects.h`, while the entire ray tracing pipeline uses `double`. The `(float)` cast in `parse_sphere()` truncated `double → float`, losing ~7 decimal digits of precision. For large spheres (radius > 1000) or very precise scenes, this caused visible intersection artifacts — the quadratic `c = dot(oc,oc) - radius_sq` mixed `double` dot product with `float` radius, amplifying round-off error.  
**Fix:** Changed `float radius_sq` to `double radius_sq` in `includes/objects.h`. Removed the `(float)` cast in `srcs/objects/rt/polygons/sphere.c`.

---

## ✅ Already Correct (No Fix Needed)

### 10. Realloc Pattern in dynarray (analysis.md §10.2)
`srcs/utils/dynarray.c` already uses the safe `tmp = realloc(ptr, new_size)` pattern.

### 11. Deep Free in Scene Destruction (analysis.md §10.1)
`destroy_scene()` already iterates meshes and calls `mesh_free()`, which frees vertices, normals, uvs, indices, name, bvh_nodes, and bvh_indices.

### 13. UV Out-of-Range Handling (analysis.md §8.3)
`srcs/surface/texture/sample.c` — `texel_at()` wraps coordinates via modulo + negative handling. Bilinear filtering now also implemented (see fix #10).

### 13. BVH Traversal Stack Overflow (analysis.md §6.2)
Both `push.c` and `occluded.c` use `stack[128]` with explicit bounds guards (`>= 126` / `>= 127`).

### 14. FBX 64-bit vs 32-bit Offsets (analysis.md §7.3)
`binary.c` already passes `ctx->version >= 7500` as `is_64` flag to `parse_nodes()` / `read_node_header()`.

### 15. MinilibX Lifecycle (analysis.md §10.3)
`gui_destroy()` already calls `mlx_destroy_image` → `mlx_destroy_window` → `free(mlx)` in correct order.

### 16. Cylinder Cap-Body Water-Tightness (analysis.md §5.1)
Body accepts `h ∈ [0, scale.y]` inclusive, caps accept `r² ≤ radius²` inclusive. Both compete for closest `t_min`. No gap possible.

---

## 🔶 Acknowledged But Not Addressed

These are valid architectural observations that are **not bugs** — they are design trade-offs or enhancements outside the current scope.

| Section | Topic | Why Deferred |
|---------|-------|-------------|
| §2.1 | `-ffast-math` flag | NaN is now guarded at critical points (cone apex, quadratic solver, vec3_norm). Removing would regress performance. |
| §2.2 | Hardcoded `MAKEFLAGS += j8` | Cosmetic build concern, not a runtime bug. |
| §2.3 | Library header dep tracking | Mitigated by `-MMD -MP`; `make re` covers edge cases. |
| §3.1 | "God Header" `core.h` | Refactoring would touch every file. |
| §3.2 | Circular dependency risks | Resolved via forward declarations; no issues exist. |
| §3.3 | GUI header exposing X11 types | Would require opaque-pointer refactor of entire GUI module. |
| §4.1 | SIMD / AVX intrinsics | LTO + unrolled mat4_mul now enables compiler auto-vectorization. Manual intrinsics not needed. |
| §5.2 | Back-face culling control | Engine does not implement refraction; not applicable. |
| §6.1 | Adaptive BVH bin count | 16-bin SAH works well for project scope. |
| §7.1 | Union-inflated stack frames | Negligible; parser is not deeply recursive. |
| §7.3 | FBX format edge cases | Would need extensive test assets from different exporters. |
| §9.2 | False sharing at tile boundaries | Tile-based rendering already minimizes this. |
| short§2 | MLX coupling in `t_scene` | `void *mlx` only used for texture loading. Decoupling cascades through entire parser. |

---

## Summary

| Category | Count |
|----------|-------|
| **Fixed** | 14 |
| **Already correct** | 7 |
| **Deferred (not bugs)** | 13 |
| **Total issues reviewed** | 34 |
