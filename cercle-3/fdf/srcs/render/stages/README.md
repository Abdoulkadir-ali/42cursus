# Render Stages Module

Handles the high-level render pipeline split into culling, geometry preparation, rasterization, and projection helpers. This subtree is responsible for deciding whether the map should be drawn, preparing the geometry representation for the current frame, and transforming map points into screen space.

---

## Directory Structure
- `srcs/render/stages/` — Render stage root
- `culling/` — Visibility tests and visible-area estimation
- `pipeline/` — Frame-level stage orchestration, adaptive detail, tessellation, and rasterization
- `projections/` — Matrix construction and point transformation helpers

---

## How It Works

### Global Pipeline
1. `redraw` calls `render_scene`.
2. `render_scene` first checks overall visibility through `is_map_visible`.
3. If the map is off-screen, the frame buffers are cleared and the frame ends early.
4. Otherwise `geometry_processing` selects the geometry representation for the frame.
5. That choice can keep the base map, apply level-of-detail stepping, or generate a tessellated submap.
6. `rasterization` then clears the frame, resets optional horizon-culling state, caches transformed points, and draws the grid.
7. Projection helpers in `projections/` build and apply the camera transform matrix used throughout the frame.

### Subtree Responsibilities
- `culling/` answers "should this map or primitive be drawn?"
- `pipeline/` answers "what geometry should be drawn this frame, and how is the frame assembled?"
- `projections/` answers "how do map-space points become screen-space points?"

---

## Developer Notes
- This subtree is stage-oriented rather than feature-oriented.
- The graphics layer calls into these helpers, but ownership of the actual image buffers remains outside this subtree.
- Visibility, geometry selection, and projection are deliberately separated so each stage can be tuned independently.

For function declarations, see `includes/render.h`.