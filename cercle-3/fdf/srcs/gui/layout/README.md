# GUI Layout Module

Handles the composition of GUI information into titled sections and reusable key/value rows. This subtree is responsible for turning runtime state into readable panel content.

---

## Directory Structure
- `srcs/gui/layout/` — Layout root
- `layout.c` — Base layout cursor and text-placement helpers
- `style.c` — GUI style display section
- `axis/` — Axis indicator drawing helpers
- `map/` — Current map display
- `performance/` — Optimization and projection metrics
- `titles/` — Controls guide and section helpers
- `transform/` — FPS and transform-stat sections

---

## How It Works

### Global Pipeline
1. A panel redraw starts with a fresh `t_layout`.
2. `gui_layout_init` seeds the cursor position and panel metrics.
3. Section helpers add titles, labels, and key/value pairs in order.
4. Specialized folders render content for controls, map selection, optimization state, and transform data.
5. The composed panel is then displayed through the GUI image.

---

## Developer Notes
- The layout engine is cursor-based and intentionally simple.
- Sections are independent and consume shared `t_gui` state through a `t_layout` wrapper.
- Direct overlays like the axis indicator live beside the panel system because they draw straight to the window.

For exported declarations, see `includes/gui.h`.