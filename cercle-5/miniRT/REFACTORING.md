# miniRT — Refactoring Checklist

Full codebase audit covering **DRY**, **Separation of Concerns**, **Performance**, **Clarity**, and **Best Practices**.

---

## 🔴 DRY (Don't Repeat Yourself)

### D1 · `ensure_capacity` duplicated 3 times
| Copy | File | Signature |
|------|------|-----------|
| 1 | `srcs/scene/add.c:19` | `(void**, int*, int*, size_t)` |
| 2 | `srcs/surface/material/add.c:19` | identical copy |
| 3 | `srcs/objects/obj/parsing/obj_parser.c:46` | `(void**, size_t, size_t*, size_t)` — different param types |

**Fix:** Extract one canonical version into a shared utility (e.g. `srcs/utils/dynarray.c`). All three callers should use it.

---

### D2 · AABB slab-test intersection duplicated
| Copy | File | Lines |
|------|------|-------|
| 1 | `srcs/raytracing/bvh/traverse.c:43–89` | `aabb_intersect_fast` |
| 2 | `srcs/objects/obj/mesh/mesh_trace.c:56–104` | `aabb_intersect_mesh` |

Both are identical 50-line functions with the same logic.

**Fix:** Keep one in a shared header (e.g. `includes/bvh.h` as `static inline`) and delete the other.

---

### D3 · `aabb_surface_area` duplicated
| Copy | File |
|------|------|
| 1 | `srcs/raytracing/bvh/tree.c:61` |
| 2 | `srcs/objects/obj/mesh/bvh_build.c:44` |

Identical function.

**Fix:** Move to `bvh.h` or a shared AABB utility.

---

### D4 · Triangle intersection duplicated
| Copy | File | Function |
|------|------|----------|
| 1 | `srcs/objects/obj/mesh/triangle.c:23` | `intersect_triangle` |
| 2 | `srcs/objects/obj/mesh/mesh_trace.c:15` | `intersect_triangle_inline` |

Same Möller-Trumbore algorithm. The inline version has slightly different variable names but identical math.

**Fix:** Keep one version (the inline one for performance) and remove the standalone `triangle.c` or make it a thin wrapper.

---

### D5 · Identity-transform check duplicated
Two copies of the same 8-field comparison in `mesh_trace.c`:
- `intersect_mesh` (line 191–196)
- `mesh_occluded` (line 282–287)

**Fix:** Extract `is_identity_transform(t_transform *t)` as a `static inline` helper.

---

### D6 · Type-switch dispatch repeated ×4
The `if (ref.type == TYPE_SPHERE) ... else if (TYPE_PLANE) ...` chain appears in:
1. `traverse.c:intersect_object` (line 17–38)
2. `traverse.c:bvh_occluded` leaf handling (line 199–218)
3. `shading.c:get_material` (line 66–99)
4. `bound.c:aabb_from_ref` (line 112–129)

Adding a new object type requires editing 4+ files.

**Fix:** Use function pointer tables indexed by `t_type`, or at minimum extract `get_mat_id(scene, ref)`.

---

### D7 · Cone and Cylinder RT parsers are near-identical
`srcs/objects/rt/parsing/polygons/cone.c` and `cylinder.c` share the same parse pattern:
- `parse_vec3 → parse_vec3 → parse_double → parse_double → parse_vec3`
- Same zero-vector fallback logic
- Same scale assignment pattern

**Fix:** Factor into a shared helper for axis-aligned body primitives.

---

### D8 · FOV clamping repeated ×3
Min/max FOV clamp (10–170) appears in:
1. `srcs/gui/render/loop.c:update_fov`
2. `srcs/gui/input/mouse.c:handle_scroll`
3. `srcs/gui/input/mouse.c:handle_mouse_zoom_drag`

**Fix:** `clamp_fov(double *fov)` in a shared GUI util.

---

### D9 · Ray generation code duplicated
Pixel→ray calculation in `render.c` exists in both:
- `process_pixel` (line 68–108)
- `handle_hover` (line 223–247)

**Fix:** Extract `make_camera_ray(ctx, x, y)`.

---

### D10 · `inv_dir` + `sign[]` computation duplicated
`trace.c:ray_init` and `trace.c:ray_normalize_direction` repeat the same 4-line block.

**Fix:** Extract a `ray_compute_inv(t_ray *ray)` helper.

---

### D11 · Manual AABB min/max instead of `aabb_union()`
`bvh_build.c` (lines 122–127, 136–141, 152–158) manually expands min/max component-wise 6 lines at a time, instead of calling the already-existing `aabb_union()`.

Same issue in `obj_parser.c:add_vertex` (lines 147–152).

**Fix:** Use `aabb_union()` and `aabb_expand_point()` helpers.

---

### D12 · Stale docblock comments duplicated
Several polygon parsers (`plane.c`, `cylinder.c`, `cone.c`) have two `/**` doc comments stacked — one referencing a deleted token-based API, one for the current parser API.

**Fix:** Delete the stale `@param tokens` comments.

---

## 🟡 Separation of Concerns

### S1 · Debug `printf`/`fflush` scattered across production code
**~60+ occurrences** across the entire codebase in non-debug files:

| File | Count | Severity |
|------|-------|----------|
| `obj_parser.c` | 10+ | Medium |
| `fbx_binary.c` | 10+ | Medium |
| `parse.c` | 15+ | Medium |
| `mesh_bake.c` | 8 | Medium |
| `parser_core.c` | 3 | Low |
| `mtl_parser.c` | 3 | Low |
| `load.c` (texture) | 1 | Low |
| **`shading.c:87–98`** | **4** | **🔴 Critical** — in per-pixel hot path, not thread-safe |

> [!CAUTION]
> `shading.c:get_material` has a `static int dbg_cnt` counter accessed by 12 threads simultaneously. This is a **data race**.

**Fix:** Gate all debug output behind `#ifdef DEBUG`. The `debug/` module already exists — use it properly or strip the inline prints.

---

### S2 · Dead static debug counters
`mesh_trace.c:189–190` declares `static int mesh_hits` and `static int aabb_hits` that are:
- Never read
- Not thread-safe
- Pure dead code

**Fix:** Remove them.

---

### S3 · `render.c` is a monolith (280 lines, 3 concerns)
Mixes:
- Ray tracing (`process_pixel`, `render_tile_worker`)
- UI panel drawing (`draw_panel`, `draw_ui`)
- Mouse hover ray casting (`handle_hover`)

**Fix:** Split into:
- `gui/render/trace.c` — pixel rendering
- `gui/render/overlay.c` — UI text overlay
- `gui/render/hover.c` — mouse picking

---

### S4 · `loop.c` uses `static bool` for frame state
`render_loop` (line 149) uses `static bool last_dirty` — hidden mutable state.

**Fix:** Move into `t_render_ctx` struct.

---

### S5 · `sprintf` without bounds checking
`draw_ui` in `render.c:210–217` uses `sprintf(buf, ...)` with a 128-byte buffer.

**Fix:** Replace with `snprintf(buf, sizeof(buf), ...)`.

---

### S6 · Empty / stub source files polluting the build
| File | Content |
|------|---------|
| `srcs/raytracing/postprocess/texture.c` | `/* Relocated heavily */` |
| `srcs/maths/vectors/vec3.c` | `/* moved to header */` |
| `srcs/maths/vectors/vec2.c` | likely same |

**Fix:** Remove from source tree and Makefile.

---

### S7 · GLB parser has inline JSON parser
`glb_parser.c` contains a hand-written JSON key-finder (`json_find_key`, `json_get_int`) that navigates raw strings with `ft_strnstr`.

This is fragile (no proper nesting, no escape handling) and tightly coupled to the GLB format.

**Fix:** Either keep it isolated (it already is) but add comments documenting limitations, or separate into `parser/json_minimal.c`.

---

## 🔵 Performance

### P1 · Planes excluded from BVH → O(N) per ray
`trace_ray` in `trace.c:52–64` does a brute-force linear scan of **all planes** for **every ray** (primary + shadow). Planes are never added to the BVH (`collect_objects` in `tree.c` skips them).

Shadow rays in `shading.c:is_in_shadow` also scan all planes linearly (line 30–40).

With N planes and L lights, every pixel costs **O(N × L)** extra tests.

**Fix:** Since planes have infinite AABB, keep the linear scan but **exit early on first occlusion** (for shadow rays — this is already done). For primary rays, this is unavoidable unless you clip planes to scene bounds.

---

### P2 · BVH SAH build has dead O(N) loop
`tree.c:118–134` accumulates `accum_l` in a loop that **never uses the result**. The actual SAH begins at line 137 with a separate binned approach.

**Fix:** Delete lines 118–134 entirely. They are dead code.

---

### P3 · BVH SAH: 4 sorts per recursion level
In `tree.c:build_recursive`:
1. Sort on X-axis (line 108)
2. Sort on Y-axis (line 109)
3. Sort on Z-axis (line 110)
4. **Re-sort** on best axis (line 167–169)

That's 4× `qsort` calls per recursion level.

**Fix:** Skip the final re-sort if `best_axis` was the last axis tested (axis 2). Or cache the sorted order.

---

### P4 · `handle_hover` traces a full ray every frame
`render.c:handle_hover` calls `bvh_intersect` (full mesh traversal) on every frame, even if the mouse hasn't moved.

**Fix:** Only re-trace on mouse movement. Cache the last hover result by `(mouse_x, mouse_y)`.

---

### P5 · `aabb_transform` builds full matrix for identity transform
After `mesh_apply_transform`, the mesh transform is reset to identity. But `aabb_from_ref` in `bound.c:122–127` still calls `aabb_transform(bbox, transform)`, which builds a 4×4 matrix and transforms 8 corners.

**Fix:** Check for identity transform before calling `aabb_transform`.

---

### P6 · Color arithmetic in [0,255] instead of [0,1]
`shading.c:pixel_color` divides by 255, multiplies, then multiplies by 255 again. Working in normalized [0,1] throughout and converting only at final output would eliminate redundant multiply/divide pairs.

**Fix:** Normalize colors on load, convert to integer only in `put_pixel`.

---

### P7 · `pow()` called in intersection hot paths
`cylinder.c:78` uses `pow(cy->transform.scale.x, 2)` and `cone.c:78` uses `pow(...)` for squaring. `pow()` is much slower than `x * x`.

**Fix:** Replace `pow(x, 2)` with `x * x` throughout.

---

### P8 · GLB parser calls `parse_accessor` twice for indices
`glb_parser.c:load_mesh_data` calls `parse_accessor(json, ids[3], &acc)` at line 241 and again at line 247. The second call is redundant.

**Fix:** Reuse the result from the first call.

---

## 🟢 Clarity & Best Practices

### C1 · Packed variable names reduce readability
Examples of poor variable naming:
- `bvh_build.c:100` — `double p_area` (parent area? pixel area?)
- `triangle.c:27` — `double afuv[4]` (acronym of what?)
- `bvh_build.c:200` — `int m = 0, n = count - 1` (partition indices should be `left`/`right`)
- `fdf_parser.c:148` — `int p[4]` used for (x, z, idx, counter)
- `glb_parser.c:264` — `int p[2]` for fd + unused slot

**Fix:** Use descriptive names. This improves debugging and onboarding time.

---

### C2 · `check_body_t` uses unsafe `void*` casting
`cylinder.c:128–129`:
```c
static bool check_body_t(const t_ray *ray, t_cylinder *cy, double t,
    double *tm_hit[2])
```
This takes a `double**` and accesses `tm_hit[1]` as a `t_hit*` via `(t_hit *)tm_hit[1]`. This is a type-punning violation.

**Fix:** Pass `double *tm` and `t_hit *hit` as separate parameters.

---

### C3 · `main.c` declares `void *mlx` mid-block
`main.c:67` — `void *mlx = mlx_init();` is a C99 mixed declaration in a function that otherwise follows C89 conventions.

**Fix:** Declare at top of block, or consistently use C99 throughout.

---

### C4 · `realloc` partial failure in `obj_parser.c:add_vertex`
Lines 118–127: Three separate `realloc` calls. If the 2nd or 3rd fails, the previous successful realloc pointer is leaked (saved in `nv`/`nn`/`nt`), and the original `ctx->out_v` etc. are lost.

**Fix:** Use a wrapper that handles the failure atomically, or check-and-assign each one before calling the next.

---

### C5 · `parse_face` uses fixed-size array for fan triangulation
`obj_parser.c:parse_face` uses `int v[3], vt[3], vn[3]` and manually shifts elements for fan triangulation. The shift logic (`v[1] = v[2]`) at line 213 works but is confusing.

**Fix:** Rename to `prev_v`, `prev_vt`, `prev_vn` for clarity, or use explicit variable names.

---

### C6 · No `-Werror` / `-Wextra` in common build?
`for` loop variables declared in loop headers (`for (int i = ...)`) throughout `bvh_build.c` and `tree.c` may not compile with strict C89 flags used in 42 projects.

**Fix:** Verify Makefile flags. If targeting C99, be consistent. If targeting C89/Norm, move declarations to block start.

---

### C7 · `fprintf(stderr, ...)` mixed with `printf(...)` for errors
Error messages inconsistently use `stderr` (in `main.c`) vs `stdout` (everywhere else).

**Fix:** All error messages → `fprintf(stderr, ...)`. All debug messages → `printf(...)` (or better, gated behind `#ifdef DEBUG`).

---

### C8 · Memory leaks in error paths
- `create_scene` (line 55): if `ft_strdup(name)` fails, `s` is passed to `destroy_scene` which calls `free(scene->name)` on NULL — safe, but no error message
- `glb_parser.c:286–293`: cleanup chain uses comma-chained expressions `(free(), free(), true)` which is hard to read and easy to break
- `fdf_parser.c:209–211`: same comma-chain pattern

**Fix:** Use explicit cleanup labels or at minimum keep one free-per-line for readability.

---

### C9 · Magic numbers
- `parser_core.c:99` — `1000000` safety limit with no named constant
- `render.c` — tile sizes, panel dimensions
- `shading.c` — `SHADOW_BIAS`, `MAX_VALUE` OK but `1e-6` used inconsistently vs `EPSILON`

**Fix:** Define named constants (`MAX_PARSE_ITERATIONS`, `MIN_FOV`, `MAX_FOV`, etc.).

---

## Priority Order (Recommended)

1. **P2** — Delete dead SAH loop (5 min, zero risk)
2. **S1** — Gate debug printf behind `#ifdef DEBUG` (30 min, high impact)
3. **S2** — Remove dead static counters (2 min)
4. **D1** — Unify `ensure_capacity` (15 min)
5. **D2** — Merge AABB intersection (10 min)
6. **D3** — Merge `aabb_surface_area` (5 min)
7. **D5** — Extract `is_identity_transform` (5 min)
8. **D10** — Extract `ray_compute_inv` (5 min)
9. **P7** — Replace `pow(x,2)` with `x*x` (5 min)
10. **C2** — Fix unsafe `void*` cast in `check_body_t` (10 min)
11. **D4** — Merge triangle intersection (10 min)
12. **D9** — Extract camera ray helper (10 min)
13. **S3** — Split `render.c` (20 min)
14. **P3** — Optimize BVH sorts (15 min)
15. **P4** — Cache hover result (10 min)
16. **S6** — Remove empty stub files (5 min)
17. **D12** — Delete stale docblock comments (5 min)
18. **C4** — Fix realloc failure handling (15 min)
19. **D8** — FOV clamping helper (5 min)
20. **C1/C5/C9** — Naming + magic numbers (ongoing)

---

## 🔴 Additional DRY — Second Audit Pass

### D13 · `mat4_identity` and `mat4_id` are identical
`includes/maths.h` defines two functions that produce the same 4×4 identity matrix:
- `mat4_identity` (line 209)
- `mat4_id` (line 236)

Both use the exact same `(i == j)` loop. `mat4_id` is never referenced with a different signature.

**Fix:** Delete `mat4_id`. Replace all call sites with `mat4_identity`.

---

### D14 · UV orthonormal basis ("stable up vector") repeated ×4
The pattern for generating tangent/bitangent from a normal is copy-pasted in:
1. `raytracing/intersection/sphere.c:39–43`
2. `raytracing/intersection/plane.c:23–32`
3. `raytracing/intersection/cylinder.c:34–39`
4. `raytracing/intersection/cone.c:24–29`

Each uses:
```c
if (fabs(n.y) > 0.9) u_ax = vec3(1,0,0); else u_ax = vec3(0,1,0);
v_ax = vec3_norm(vec3_cross(n, u_ax));
u_ax = vec3_norm(vec3_cross(v_ax, n));
```

**Fix:** Extract `void vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent, t_vec3 *bitangent)` in `maths.h`.

---

### D15 · Mesh init/cleanup reimplemented per parser
Every mesh parser (FBX ASCII, FBX Binary, GLB, FDF, OBJ) manually allocates and frees `vertices`, `normals`, `uvs`, `indices` plus `name`. Error-path cleanup is scattered as inline `free()` chains.

| Parser | Alloc Location | Cleanup Location |
|--------|---------------|------------------|
| FDF | `fdf_init_mesh` (line 172) | `parse_fdf` error paths (line 209) |
| GLB | `load_mesh_data` (line 238) | `parse_glb` else-branch (line 292) |
| OBJ | `init_obj_ctx` / `finish_obj` | `free_obj_ctx` + inline `free` (line 302) |
| FBX ASCII | inline in `parse_fbx_ascii` | scattered `free` blocks |
| FBX Binary | inline in `parse_fbx_binary` | scattered `free` blocks |

**Fix:** Create `mesh_alloc(int v_count, int i_count)` and `mesh_free(t_mesh *mesh)` in `srcs/objects/mesh_utils.c`.

---

### D16 · File path resolution logic duplicated ×3
The "find last `/`, extract directory, join with filename" logic appears in:
1. `fbx_ascii.c:resolve_fbx_path` (line 15)
2. `mtl_parser.c:resolve_path` (line 21)
3. `obj_parser.c:handle_mtllib` (inline, line 236)

All three use `ft_strrchr(path, '/')` → `ft_substr` → `ft_strjoin`.

**Fix:** Extract `char *path_get_dir(const char *filepath)` into `srcs/utils/path_utils.c`.

---

### D17 · 12 keyboard movement functions are trivial boolean setters
`keyboard.c` has 12 separate `static void` functions (6 directions × press/release):
```c
static void move_forward_press(t_gui *gui)  { gui->cam_ctrl.moving_forward = true; }
static void move_forward_release(t_gui *gui){ gui->cam_ctrl.moving_forward = false; }
// ... same for backward, left, right, up, down
```

Each is a single-line function that sets one boolean.

**Fix:** Replace with a generic `set_movement_flag(t_gui *gui, int offset, bool value)` using `offsetof`, reducing 12 functions to 1.

---

### D18 · Dynamic array growth in `fbx_ascii.c:parse_array`
`parse_array` (line 87) implements manual `malloc` + `realloc` with capacity doubling — the same pattern as `ensure_capacity` (D1), but with a different signature and initial capacity (10000 vs 16).

**Fix:** Consolidate with the unified `ensure_capacity` from D1.

---

### D19 · Whitespace skipping reimplemented ×4
| Implementation | File | Style |
|---------------|------|-------|
| `skip_whitespace(char**)` | `rt/parsing/utils.c:20` | Advances `char **` pointer |
| `parser_skip_whitespace(t_parser*)` | `parser/parser_core.c` | Uses buffered parser |
| `fbx_next(char*)` | `fbx_ascii.c:30` | Skips non-digit chars |
| inline `while (*p == ' ')` | `mtl_parser.c:44,51,64` | Manual loops |

**Fix:** Consolidate the `char**`-advancing versions into a single utility.

---

### D20 · Number parsing fragmented across 3+ implementations
| Function | File | Backend |
|----------|------|---------|
| `parse_float_fast` | `rt/parsing/utils.c:29` | `strtod` + manual skip |
| `f_vec3` / `f_int` | `fbx_ascii.c:119` | `strtod` / `ft_atoi` |
| `parse_double` | `parser/parser_values.c` | `ft_strtod` |
| `ft_strtod` | `libft` | Full implementation |
| `ft_strtof` | `libft` | Wraps `ft_strtod` with cast |

`ft_strtof` is literally `return ((float)ft_strtod(s))` — 1 line.

**Fix:** Standardize on `ft_strtod` for all parsing. Consider removing `ft_strtof` if unused.

---

## 🟡 Additional Separation of Concerns

### S8 · FBX ASCII parser mixes I/O, parsing, and scene construction
`parse_fbx_ascii` in `fbx_ascii.c` does everything in one function:
- Reads entire file into memory (`open` → `read` → close)
- Searches for FBX node strings
- Parses arrays into mesh data
- Calls `mesh_build_bvh` and `scene_add_mesh`

**Fix:** Decompose into `fbx_read_file` (I/O), `fbx_parse_nodes` (data), `fbx_to_scene` (conversion).

---

## 🔵 Additional Performance

### P9 · `repack_doubles_to_vec3` allocates intermediate buffer
`fbx_binary.c:repack_doubles_to_vec3` allocates a new `t_vec3*` array and iterates to cast from `double`. This creates an allocation + copy for every vertex/normal array.

**Fix:** Parse directly into `t_vec3` on the fly, avoiding the intermediate buffer.

---

## Updated Priority Order (Items 21–30)

21. **D13** — Delete `mat4_id` (2 min, zero risk)
22. **D14** — Extract `vec3_orthonormal_basis` (10 min)
23. **D15** — `mesh_alloc`/`mesh_free` utility (15 min)
24. **D16** — `path_get_dir` utility (10 min)
25. **D17** — Consolidate keyboard movement functions (10 min)
26. **D18** — Merge FBX `parse_array` with unified dynarray (5 min)
27. **D19** — Consolidate whitespace skipping (10 min)
28. **D20** — Standardize number parsing (15 min)
29. **S8** — Decompose FBX ASCII parser (30 min)
30. **P9** — Eliminate repack intermediate buffer (15 min)
