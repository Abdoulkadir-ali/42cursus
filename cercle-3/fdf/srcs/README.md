# 🧩 **Source Tree** - *FDF Engine Layout*

> **The internal map of the renderer**  
> A guided overview of how the `srcs/` directory is organized, how data flows
> through the engine, and where each runtime responsibility lives.

![Architecture](https://img.shields.io/badge/Architecture-Modular-1f6feb?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Rendering](https://img.shields.io/badge/Pipeline-Real--Time-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Docs-Complete-success?style=for-the-badge)

---

## 📖 **Overview**

The `srcs/` directory contains the full FDF runtime engine. It is split into
small, focused modules so the application can load terrain data, transform it
through the camera and render pipeline, respond to user input, and present a
live GUI overlay without collapsing responsibilities into one large subsystem.

At a high level, the source tree follows this sequence:

1. **Core** boots the application and wires runtime state together.
2. **Geometry** loads or generates map data.
3. **Render** prepares camera transforms and projection state.
4. **Graphics** rasterizes lines, grids, pixels, and triangles into buffers.
5. **GUI** draws the overlay and runtime status panels.
6. **Events** keeps the whole system interactive through mouse, keyboard, and loop hooks.

---

## 🗂️ **Directory Atlas**

| Directory | Responsibility | Highlights |
| :--- | :--- | :--- |
| `core/` | Application bootstrap and shutdown | argument handling, initialization, cleanup |
| `events/` | Runtime input system | hooks, key maps, mouse actions, live toggles |
| `geometry/` | Terrain and map data | file loading, styling, generation, tessellation |
| `graphics/` | Low-level drawing engine | frame buffers, grid traversal, Bresenham, triangle fill |
| `gui/` | Overlay and HUD rendering | panels, labels, formatting, themes, transforms |
| `primitives/` | Math foundations | vectors, matrices, clamp helpers |
| `render/` | Camera and render stages | projections, culling, LOD, raster flow |
| `window/` | Window bootstrap | MLX window creation and initial setup |

---

## ⚙️ **Runtime Pipeline**

### **1. Startup**
- `core/` creates the main runtime objects.
- `window/` opens the MLX window and backing surfaces.
- `graphics/` allocates frame buffers, depth buffers, and draw state.

### **2. Data Preparation**
- `geometry/map/read/` loads `.fdf` files from disk.
- `geometry/map/generator/` can synthesize new terrain procedurally.
- `geometry/map/style/` assigns point colors from height or source data.

### **3. Camera & Projection**
- `render/camera/` positions the scene and handles zoom, rotation, and centering.
- `render/stages/projections/` transforms world-space geometry into screen-space coordinates.
- `render/stages/culling/` removes geometry that should not be drawn.

### **4. Rasterization**
- `graphics/draw/grid/` traverses mesh lines and segments.
- `graphics/draw/lines/` handles clipped and unclipped line rendering.
- `graphics/draw/triangle/` fills triangles and scanlines when filled rendering is active.

### **5. Interface & Interaction**
- `gui/` renders the information overlay, sections, titles, theme colors, and status values.
- `events/` updates flags, toggles rendering options, and drives the main loop hook.

### **6. Shutdown**
- `core/cleanup.c` releases maps, graphics buffers, MLX resources, and runtime allocations.

---

## 🧠 **Design Principles**

| Principle | How It Appears in `srcs/` |
| :--- | :--- |
| **Separation of Concerns** | Input, geometry, rendering, GUI, and startup are isolated into separate folders. |
| **Pipeline Thinking** | Data moves from map loading to transform stages to rasterization in clear steps. |
| **Performance Awareness** | Threaded loading, render culling, LOD, and targeted tessellation reduce wasted work. |
| **Replaceable Components** | Map styles, projections, controls, and draw strategies can evolve without rewriting the whole engine. |

---

## 🔍 **Module Relationships**

```text
core -> window -> graphics
core -> geometry -> render -> graphics
events -> render
events -> graphics
events -> geometry
gui -> graphics
primitives -> geometry / render / graphics / gui
```

This structure keeps the math layer reusable, the rendering path deterministic,
and the event system focused on mutating state rather than performing draw work directly.

---

## 🧭 **Where To Look First**

If you are exploring the engine for the first time, this route gives the clearest picture:

1. Start with `core/` to understand the application entry path.
2. Read `geometry/` to see how maps are loaded and prepared.
3. Move into `render/` to understand transforms, camera state, and culling.
4. Open `graphics/` for the actual draw pipeline.
5. Finish with `events/` and `gui/` for interaction and overlay behavior.

---

## 🛠️ **Developer Notes**

- Each major folder now has its own local `README.md` for detailed subsystem-level guidance.
- Headers in the source tree are intentionally small and descriptive so each directory remains navigable.
- The engine is modular enough that most feature work stays contained within one subsystem plus a small number of shared headers.
- `primitives/` is the lowest-level reusable layer and is depended on by nearly every other module.

---

## 📚 **Related Files**

- Project overview: `/README.md`
- Public interfaces: `/includes/`
- Build entry: `/Makefile`
- Test and sample terrain: `/maps/`

---

<center>
  <sub>The `srcs/` tree is the engine room of FDF: data in, transforms through, pixels out.</sub>
</center>