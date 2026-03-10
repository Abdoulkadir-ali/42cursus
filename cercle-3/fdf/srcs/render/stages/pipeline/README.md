# Pipeline Stage

Handles frame orchestration, adaptive geometry selection, tessellation, level-of-detail stepping, and rasterization setup. This stage is responsible for choosing what geometry representation to draw and for launching the actual frame build.

---

## Directory Structure
- `srcs/render/stages/pipeline/` — Frame pipeline helpers
- `render.c` — Top-level render entry for the stage subtree
- `geometry.c` — Geometry-mode selection and detail-level routing
- `adaptive.c` — Adaptive detail heuristic
- `tesselation.c` — Visible-region tessellation and tessellation cache reuse
- `lod.c` — Coarser sampling configuration
- `rasterization.c` — Frame clear, projection cache setup, and grid draw launch

---

## How It Works

### Global Pipeline
1. `render_scene` validates the graphics context.
2. It asks the culling stage whether the current map is visible.
3. If not visible, it only clears the frame buffers.
4. If visible, it calls `geometry_processing`.
5. `geometry_processing` computes an effective detail level through `calculate_geometry_level`.
6. It routes that level through `apply_geometry_mode`.
7. Positive levels enable tessellation, negative levels enable LOD stepping, and zero keeps the base map.
8. After geometry selection, `rasterization` clears frame data, resets the optional horizon buffer, caches projections, and launches `draw_grid`.

### Geometry Selection
1. `calculate_geometry_level` enforces a minimum level for filled and triangle modes.
2. When adaptive logic is enabled, it asks `calculate_adaptive_level` for the preferred level.
3. `apply_geometry_mode` then decides whether to keep `base_map`, generate a tessellated submap, or use stepped LOD drawing.

### Tessellation Path
1. `apply_tesselation` stores the requested tessellation level.
2. It asks the culling stage for the visible map bounds.
3. It reuses the cached tessellated map if the level and bounds match the previous frame.
4. Otherwise it generates a new tessellated submap for the visible region.

### LOD Path
1. `apply_lod` converts the negative level into a power-of-two step.
2. It stores that step in `render_config.lod_value`.
3. It reverts the active map to `base_map` and clears any tessellated map.

---

## Developer Notes
- This folder chooses the geometry representation but does not itself perform per-point projection math.
- The adaptive heuristic is scale-aware and target-point-budget-aware.
- Rasterization here is stage setup, not the low-level triangle scanline raster code used elsewhere in the graphics subsystem.

For exported declarations, see `includes/render.h`.