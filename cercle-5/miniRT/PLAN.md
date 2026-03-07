# miniRT — Material & Scene Manager GUI: Implementation Plan

> **Target map:** `maps/rt/change.rt` (sphere + ambient + point-light + ground plane)  
> **Norm:** All new C files follow 42 Norm — tabs, no ternaries, no assignment-in-condition, declarations before statements, max 25 lines per function.

---

## 1. Goal Overview

Build an interactive, real-time editor layer on top of the existing raytracer, inspired by Blender / Unreal Engine 5:

| Feature | Description |
|---|---|
| **Hover tooltip** | Mouse-over any surface → show object type + index |
| **Click selection** | Left-click → select the hit object (highlight in scene panel) |
| **Scene panel** | Left sidebar listing every object in the scene |
| **Inspector panel** | Right sidebar showing properties of the selected object |
| **Transform editor** | Edit position, rotation, scale of selected object in real time |
| **Material editor** | Edit color, roughness, metallic, opacity, reflectivity of the material |
| **Object CRUD** | Add / delete spheres, planes, cylinders, lights from GUI buttons |
| **Live re-render** | Any change sets `render.dirty = true` + optional BVH rebuild |

---

## 2. Test Scene — `maps/rt/change.rt`

```
A 0.15 255,255,255
C 0,2,10 0,0,-1 60
L 3,5,5 0.8 255,220,180
sp 0,0,0 1.5 180,100,255
pl 0,-2,0 0,1,0 80,80,80
```

One sphere, one plane, one point-light, one ambient — enough to demonstrate every
editor feature with zero noise.

---

## 3. Current Architecture Audit

### 3.1 What already exists

| System | Location | State |
|---|---|---|
| Widget list (label, checkbox) | `srcs/gui/widget/` | Partial — no slider/button draw |
| Panel drawing | `srcs/gui/render/overlay/panel.c` | Working |
| Hover ray-cast | `srcs/gui/render/hover.c` | Minimal: only "Object hit" string |
| Mouse click handler | `srcs/gui/input/mouse/buttons.c` | No selection logic |
| Material struct (PBR) | `includes/surface.h` | Complete |
| Scene struct | `includes/scene.h` | Complete |
| BVH intersect | `srcs/rays/` | Complete |
| `t_hit` (type + index ref) | `includes/raytracing.h` | Complete |

### 3.2 What is missing

- **Selection state** in `t_gui`
- **Editor panels** (scene list, inspector, material)
- **Slider widget** (draw + mouse-drag interaction)
- **Button widget** (draw + click callback)
- **Object CRUD** functions
- **BVH rebuild** trigger after transform change
- **Hover enhancement** to display object type & name

---

## 4. New Data Structures

### 4.1 `t_selection`  (`includes/editor.h`)

```c
typedef struct s_selection
{
    t_type  type;       /* TYPE_SPHERE, TYPE_PLANE, etc. */
    int     index;      /* Index in scene array          */
    bool    active;     /* Is anything selected?         */
    t_aabb  bbox;       /* Cached world AABB for outline */
}   t_selection;
```

### 4.2 `t_inspector`  (`includes/editor.h`)

```c
typedef enum e_inspect_tab
{
    TAB_TRANSFORM,
    TAB_MATERIAL,
    TAB_OBJECT
}   t_inspect_tab;

typedef struct s_inspector
{
    bool            visible;
    t_inspect_tab   tab;
    int             x;          /* Panel left edge (screen coords) */
    int             width;      /* Default 280 px                  */
}   t_inspector;
```

### 4.3 `t_scene_panel`  (`includes/editor.h`)

```c
typedef struct s_scene_panel
{
    bool    visible;
    int     width;          /* Default 220 px */
    int     scroll;         /* Pixel scroll offset */
    int     hovered_row;    /* Row mouse is over   */
}   t_scene_panel;
```

### 4.4 `t_slider_state`  (`includes/editor.h`)

```c
typedef struct s_slider_state
{
    bool    dragging;
    int     drag_start_x;
    double  drag_start_val;
    t_widget *target;
}   t_slider_state;
```

### 4.5 Extensions to `t_gui`  (`includes/gui.h`)

```c
struct s_gui
{
    /* ... existing fields ... */
    t_selection     selection;
    t_inspector     inspector;
    t_scene_panel   scene_panel;
    t_slider_state  slider_state;
    t_hit           hover_hit;      /* Full hit stored by hover system */
};
```

---

## 5. New Header — `includes/editor.h`

Contains:
- `t_selection`, `t_inspector`, `t_scene_panel`, `t_slider_state`
- Function prototypes for every new editor file
- Color constants: `COL_SELECTED`, `COL_PANEL_HEADER`, `COL_SLIDER_FILL`
- Layout constants: `INSPECTOR_W`, `SCENE_PANEL_W`, `ROW_H`

---

## 6. New File Map

```
srcs/gui/editor/
    selection.c         Phase 1 — select / clear / query
    hover_info.c        Phase 7 — enhanced tooltip with type+name
    scene_panel.c       Phase 2 — left sidebar object list
    inspector.c         Phase 3 — right sidebar panel dispatcher
    transform_panel.c   Phase 3 — position / rotation / scale section
    material_panel.c    Phase 4 — color / PBR sliders
    object_ops.c        Phase 6 — add_sphere / add_plane / delete_selected

srcs/gui/widget/
    slider.c            Phase 5 — WIDGET_SLIDER draw + drag
    button.c            Phase 5 — WIDGET_BUTTON draw + click
```

All object files are automatically picked up by the Makefile via `find srcs -name "*.c"`.

---

## 7. Phased Implementation

---

### Phase 1 — Selection Backbone

**Files:** `includes/editor.h`, `srcs/gui/editor/selection.c`,  
`includes/gui.h` (extend `t_gui`), `srcs/gui/input/mouse/buttons.c` (extend left-click)

#### `selection.c` functions

```
select_object(gui, type, index)   /* Set gui->selection, cache AABB */
clear_selection(gui)               /* Wipe gui->selection.active     */
get_selected_material(gui)         /* Return *t_material or NULL      */
pick_at_mouse(gui, ctx)            /* Ray-cast, call select_object    */
```

#### Left-click extension in `buttons.c`

```c
if (button == BUTTON_LEFT)
{
    widget_handle_mouse(gui, button, mouse);
    if (!widget_consumed)            /* New: pass-through flag */
        pick_at_mouse(gui, &ctx);
    gui->cam_ctrl.mouse_left_pressed = true;
    gui->cam_ctrl.last_mouse = mouse;
}
```

#### BVH AABB cache

`select_object` calls `aabb_from_ref(scene, ref)` to fill `selection.bbox`
for screen-space outline drawing.

---

### Phase 2 — Scene Panel (Left Sidebar)

**Files:** `srcs/gui/editor/scene_panel.c`

**Layout:** `x=0, y=0, w=SCENE_PANEL_W, h=disp_h`

#### Functions

```
draw_scene_panel(gui)
    draw_panel background
    draw_panel_header: "Scene"
    draw_object_rows(gui)
    draw_add_buttons(gui)

draw_object_rows(gui)
    iterate spheres, planes, cylinders, cones, lights, meshes
    each row: type icon char + name + click = select

draw_add_buttons(gui)
    "+ Sphere"  "+ Plane"  "+ Cylinder"  "+ Light"
    (WIDGET_BUTTON callbacks to object_ops.c)

scene_panel_handle_click(gui, mouse)
    map mouse.y - header_h - scroll → row → call select_object
```

**Row format:**

```
[SP] Sphere 0           ← active selection: highlighted row
[PL] Plane 0
[LT] Light 0
```

**Scroll:** Mouse scroll wheel inside panel x-range adjusts `scene_panel.scroll`.

---

### Phase 3 — Inspector Panel (Right Sidebar)

**Files:** `srcs/gui/editor/inspector.c`, `srcs/gui/editor/transform_panel.c`

**Layout:** `x = disp_w - INSPECTOR_W, y=0, w=INSPECTOR_W, h=disp_h`

#### `inspector.c` functions

```
draw_inspector(gui)
    if !selection.active → draw "Nothing selected" hint
    else:
        draw_inspector_header(gui)         /* Shows type + index     */
        draw_tab_bar(gui)                  /* Transform | Material   */
        if tab == TAB_TRANSFORM
            draw_transform_panel(gui)
        else
            draw_material_panel(gui)

draw_inspector_header(gui)
    panel + type string ("Sphere #0")

draw_tab_bar(gui)
    two WIDGET_BUTTON: TAB_TRANSFORM / TAB_MATERIAL
    clicking sets inspector.tab + gui->render.dirty = false (UI redraw only)
```

#### `transform_panel.c` functions

```
draw_transform_panel(gui)
    draw_vec3_sliders(gui, "Position", &transform->pos, -50, 50)
    draw_vec3_sliders(gui, "Rotation", &rot_degrees, -180, 180)
    draw_vec3_sliders(gui, "Scale",    &transform->scale, 0.01, 20)

draw_vec3_sliders(gui, label, vec, min, max)
    label row
    X slider → *double target = &vec->x
    Y slider → *double target = &vec->y
    Z slider → *double target = &vec->z

on_transform_change callback (attached to each slider)
    writes new value to the actual scene object's transform
    calls transform_rebuild(scene, selection)  ← rebuilds BVH
    sets render.dirty = true
```

**Important:** Rotation display is in degrees (`pitch * RAD2DEG`).  
Slider writes back as radians (`deg * DEG2RAD`).

---

### Phase 4 — Material Panel

**Files:** `srcs/gui/editor/material_panel.c`

#### Functions

```
draw_material_panel(gui)
    mat = get_selected_material(gui)
    if !mat → return
    draw_color_sliders(gui, mat)     /* R G B each 0–255 */
    draw_double_slider(gui, "Roughness",     &mat->roughness,     0, 1)
    draw_double_slider(gui, "Metallic",      &mat->metallic,      0, 1)
    draw_double_slider(gui, "Opacity",       &mat->transparency,  0, 1)
    draw_double_slider(gui, "Reflectivity",  &mat->reflectivity,  0, 1)
    draw_double_slider(gui, "IOR",           &mat->refract_index, 1, 3)
    draw_emission_sliders(gui, mat)  /* R G B emission */

draw_color_sliders(gui, mat)
    three sliders for mat->albedo_map.color_a (x=R, y=G, z=B in [0,1])
    on_change: dirty = true (material already in-place)

draw_emission_sliders(gui, mat)
    three sliders for mat->emission (x=R, y=G, z=B in [0, 5] for HDR)
```

**No copy needed:** materials live in `scene->materials[mat_id]`, slider
callbacks mutate them directly → next render picks up the change.

---

### Phase 5 — Widget Extensions

#### `srcs/gui/widget/slider.c`

```
draw_slider(gui, w)
    draw track rect (COL_BORDER)
    fill fraction = (w->dvalue - w->dmin) / (w->dmax - w->dmin)
    draw filled portion (COL_ACCENT)
    draw knob circle at fill_x
    draw label + value text

slider_begin_drag(gui, w, mouse_x)
    gui->slider_state.dragging = true
    gui->slider_state.target   = w
    gui->slider_state.drag_start_x   = mouse_x
    gui->slider_state.drag_start_val = w->dvalue

slider_update_drag(gui, mouse_x)
    delta_px = mouse_x - drag_start_x
    range    = w->dmax - w->dmin
    w->dvalue = clamp(drag_start_val + delta_px * range / w->size.x, dmin, dmax)
    if w->on_change: w->on_change(w, gui)

slider_end_drag(gui)
    gui->slider_state.dragging = false
    gui->slider_state.target   = NULL
```

Widget struct needs two new fields added to `t_widget`:
```c
double  dmin;
double  dmax;
void    *target;   /* pointer to the double to mutate */
```

Standard `on_change` for "mutate-and-dirty" pattern:
```c
void    slider_write_double(t_widget *w, t_gui *gui)
{
    *(double *)w->target = w->dvalue;
    gui->render.dirty = true;
}
```

#### `srcs/gui/widget/button.c`

```
draw_button(gui, w)
    filled rect (COL_BORDER)
    if hovered: fill COL_HOVER
    center label text

widget_handle_mouse already calls on_click — no additional hook needed.
```

#### Changes to `srcs/gui/widget/draw.c`

Extend `widget_draw_all` dispatch:
```c
else if (w->type == WIDGET_SLIDER)
    widget_draw_slider(gui, w);
else if (w->type == WIDGET_BUTTON)
    widget_draw_button(gui, w);
```

---

### Phase 6 — Object CRUD

**Files:** `srcs/gui/editor/object_ops.c`

```
add_sphere_default(gui)
    zero-initialize t_sphere
    transform.pos = cam_ctrl.transform.pos + forward * 5
    radius = 1.0, radius_sq = 1.0
    mat_id = scene_add_fresh_material(scene, vec3(0.7, 0.7, 0.7))
    scene_add_sphere(scene, sphere)
    rebuild_bvh(gui)
    select_object(gui, TYPE_SPHERE, scene->sphere_count - 1)

add_plane_default(gui)
    same pattern, normal = (0,1,0)

add_cylinder_default(gui)
    radius=0.5, height=2.0

add_light_default(gui)
    point light at camera pos + forward*5, brightness=0.5, white

delete_selected(gui)
    swap selected index with last element in array
    decrement count
    clear_selection(gui)
    rebuild_bvh(gui)
    gui->render.dirty = true
```

**Swap-remove** avoids shifting entire arrays.  
After delete, if spheres/planes arrays are reallocated down, nothing crashes
because BVH is rebuilt fresh.

**Keyboard hook:** `Del` key → `delete_selected(gui)` (in `srcs/gui/input/keyboard/`).

---

### Phase 7 — Enhanced Hover Tooltip

**Files:** `srcs/gui/editor/hover_info.c`, extend `srcs/gui/render/hover.c`

`update_hover` stores the full `t_bvh_ref` in `gui->hover_hit.ref`.

`draw_hover_text` replaced by `draw_hover_info(gui)`:

```
draw_hover_info(gui)
    if !g_hover.active: return
    type_str = ref_type_name(gui->hover_hit.ref.type)
    snprintf(buf, "%.12s #%d", type_str, gui->hover_hit.ref.index)
    panel: x = g_hover.x + 16, y = g_hover.y - 36, w = 160, h = 32
    draw_panel
    mlx_string_put label

ref_type_name(type)
    if type == TYPE_SPHERE   → "Sphere"
    if type == TYPE_PLANE    → "Plane"
    if type == TYPE_CYLINDER → "Cylinder"
    if type == TYPE_CONE     → "Cone"
    if type == TYPE_LIGHT    → "Light"
    if type == TYPE_MESH     → "Mesh"
    return "Unknown"
```

---

### Phase 8 — Selection Outline (Bonus / Visual Polish)

After the main render is drawn on `disp_img`, `draw_selection_outline(gui)`:

```
draw_selection_outline(gui)
    if !selection.active: return
    project bbox 8 corners to screen space
    find screen-space min/max x, y
    draw_rect_border(gui, sx, sy, sw, sh, COL_SELECTED)
```

This is a 2D-screen rectangle around the AABB projection — not pixel-perfect but sufficient for a game-engine-style gizmo feel at zero render cost.

---

## 8. Render Pipeline Integration

### 8.1 Current `draw_ui_text` call chain

```
render_frame()
  → copy img to disp_img
  → draw_ui_panels()      ← add new: draw_scene_panel(), draw_inspector()
  → draw_ui_text()        ← keep existing
  → handle_hover()        ← replace draw_hover_text with draw_hover_info
```

### 8.2 New overlay draw order

```
1. draw_ui_panels()          (background panels — scene + inspector)
2. draw_scene_panel(gui)     (object rows, add buttons)
3. draw_inspector(gui)       (transform or material sliders)
4. draw_selection_outline(gui)
5. draw_ui_text()            (FPS, help, camera)
6. draw_hover_info(gui)      (topmost — tooltip above everything)
```

### 8.3 Dirty flag strategy

| Action | Result |
|---|---|
| Slider drag (material) | `dirty = true` only |
| Transform slider drag | `dirty = true` + `rebuild_bvh(gui)` |
| Add / delete object | `dirty = true` + `rebuild_bvh(gui)` |
| Tab switch in inspector | UI redraw only (skip full raytrace) |
| Hover movement | No dirty (overlay is always live) |

---

## 9. BVH Rebuild Helper

```c
/* srcs/gui/editor/selection.c */
void    rebuild_bvh(t_gui *gui)
{
    if (gui->scene->bvh)
        bvh_destroy(gui->scene->bvh);
    gui->scene->bvh = bvh_create(gui->scene);
}
```

Called only when geometry actually changes (transform or CRUD).  
Material edits skip it — BVH structure is geometry-only.

---

## 10. Norm Compliance Strategy

| Rule | Approach |
|---|---|
| Max 25 lines/function | Every `draw_X_panel` splits into `draw_X_header` + `draw_X_body` + row helpers |
| No ternaries | All `condition ? a : b` → `if/else` |
| No assign-in-condition | No `if ((x = f()) != NULL)` |
| Declarations first | All `t_widget *w; int i; double v;` before any statement |
| Variable chaining | `i = j = 0;` where multiple are zero-init |
| Return trick | `return (free(ptr), NULL);` in cleanup paths |
| Tab indentation | Every new file uses real tab characters |

---

## 11. Full File Checklist

### New files to create

- [ ] `includes/editor.h`
- [ ] `srcs/gui/editor/selection.c`
- [ ] `srcs/gui/editor/hover_info.c`
- [ ] `srcs/gui/editor/scene_panel.c`
- [ ] `srcs/gui/editor/inspector.c`
- [ ] `srcs/gui/editor/transform_panel.c`
- [ ] `srcs/gui/editor/material_panel.c`
- [ ] `srcs/gui/editor/object_ops.c`
- [ ] `srcs/gui/widget/slider.c`
- [ ] `srcs/gui/widget/button.c`

### Files to modify

- [ ] `includes/gui.h` — add `t_selection`, `t_inspector`, `t_scene_panel`, `t_slider_state` to `t_gui`; add color constants
- [ ] `srcs/gui/widget/draw.c` — add SLIDER + BUTTON dispatch in `widget_draw_all`
- [ ] `srcs/gui/widget/widget.c` — add `dmin`, `dmax`, `target` fields to widget; `widget_handle_mouse` passes slider drag through
- [ ] `srcs/gui/input/mouse/buttons.c` — left-click calls `pick_at_mouse`; mouse motion calls `slider_update_drag`
- [ ] `srcs/gui/input/mouse/motion.c` — feed x/y into slider drag if active
- [ ] `srcs/gui/input/keyboard/` — `Del` → `delete_selected`
- [ ] `srcs/gui/render/hover.c` — store `t_bvh_ref` in `gui->hover_hit`; call `draw_hover_info`
- [ ] `srcs/gui/render/overlay/panel.c` — call `draw_scene_panel` + `draw_inspector` + `draw_selection_outline`
- [ ] `srcs/gui/render/overlay/overlay.c` — include editor.h; forward new overlay calls

---

## 12. Layout Diagram

```
┌──────────────────────────────────────────────────────────────┐
│  [Scene Panel 220px]   [  Render Viewport  ]  [Inspector 280px]│
│                                                               │
│  Scene                 ┌────────────────┐   Transform        │
│  ─────────             │                │   ─────────        │
│  [SP] Sphere 0  ◄─sel  │                │   Pos X [──●───]   │
│  [PL] Plane  0         │                │   Pos Y [────●─]   │
│  [LT] Light  0         │                │   Pos Z [●──────]  │
│                        │  raytraced     │                    │
│                        │  image         │   Material         │
│                        │                │   ─────────        │
│                        │                │   R   [───●────]   │
│                        │                │   G   [─────●──]   │
│  ─────────             │                │   B   [──●─────]   │
│  + Sphere              │     hover:     │                    │
│  + Plane               │  ┌──────────┐  │   Roughness[●───]  │
│  + Cylinder            │  │Sphere #0 │  │   Metallic [──●─]  │
│  + Light               │  └──────────┘  │   Opacity  [────●] │
│                        └────────────────┘                    │
│  [POS 0.00 2.00 10.00  ROT ...]         [120 FPS]           │
└──────────────────────────────────────────────────────────────┘
```

---

## 13. Risk & Mitigation

| Risk | Mitigation |
|---|---|
| BVH rebuild is expensive on large scenes | Only rebuild on geometry change; skip for material edits |
| Slider drag and camera drag conflict | Check `slider_state.dragging` before enabling camera rotation |
| Adding objects overflows scene arrays | `scene_add_*` already uses dynamic realloc via `dynarray.c` |
| Delete leaving dangling mat_id refs | After swap-remove, update any adjacent object that referenced the swapped index |
| Function line count overflow | Pre-split each panel into header + body helpers before writing |
| 42 Norm `t_panel` compound literal | Already used in existing code — allowed |

---

## 14. Iterative Testing Approach

Each phase builds on the previous and can be compiled and tested independently:

1. **Phase 1:** Click logs to stdout which object type + index was hit.
2. **Phase 2:** Scene panel appears; clicking rows logs selection changes.
3. **Phase 3:** Inspector shows static transform values for selected object.
4. **Phase 4:** Dragging color slider changes the sphere's color visually on next render.
5. **Phase 5:** All sliders are draggable; buttons fire callbacks.
6. **Phase 6:** "+ Sphere" adds a sphere visible in both scene panel and render.
7. **Phase 7:** Hover shows "Sphere #0" tooltip instead of "Object hit".
8. **Phase 8:** Screen-space AABB outline glows around selected object.

At each step: `make re && ./miniRT maps/rt/change.rt`

---

## 15. Git Workflow — Commit Between Every Phase

Each phase ends with a mandatory commit **before** moving on.  
This creates clean restore points so any phase can be reverted independently.

### Commit procedure (end of each phase)

```bash
git add -A
git commit -m "feat(editor): Phase N — <short description>"
```

Example commit messages:

| Phase | Commit message |
|---|---|
| 1 | `feat(editor): Phase 1 — selection backbone & pick_at_mouse` |
| 2 | `feat(editor): Phase 2 — scene panel sidebar` |
| 3 | `feat(editor): Phase 3 — inspector + transform sliders` |
| 4 | `feat(editor): Phase 4 — material panel (PBR sliders)` |
| 5 | `feat(widget): Phase 5 — slider & button widgets` |
| 6 | `feat(editor): Phase 6 — object CRUD (add/delete)` |
| 7 | `feat(editor): Phase 7 — enhanced hover tooltip` |
| 8 | `feat(editor): Phase 8 — selection outline gizmo` |

### User feedback loop

After every commit the user runs `make re && ./miniRT maps/rt/change.rt` and
evaluates the result. Three outcomes are possible:

---

#### ✅ Outcome 1 — Continue

Everything works as expected. Move on to the next phase.

```bash
# Nothing extra needed — the commit is already on the branch.
```

---

#### 🐛 Outcome 2 — Fix a bug

A specific behaviour is broken but the overall design is correct.

1. Describe the bug precisely (what is wrong, how to reproduce it).
2. A targeted fix is applied to the affected file(s) only.
3. After the fix: `make re && ./miniRT maps/rt/change.rt` to verify.
4. Commit the fix on top of the phase commit:

```bash
git add -A
git commit -m "fix(editor): Phase N — <describe the bug fixed>"
```

---

#### ⏪ Outcome 3 — Revert and redo from scratch

The approach for this phase is fundamentally wrong and patching would cost more
than rewriting.

1. Identify the last good commit (the one just before the broken phase):

```bash
git log --oneline
```

2. Hard-reset to that commit (discards all uncommitted changes):

```bash
git reset --hard <commit-hash>
```

3. Re-implement the phase from scratch with the new design.
4. Commit again once stable.

> **Safety rule:** Never `git reset --hard` past a phase that was marked
> ✅ Continue by the user. Only reset the phase currently being reviewed.

---

*End of PLAN.md*
