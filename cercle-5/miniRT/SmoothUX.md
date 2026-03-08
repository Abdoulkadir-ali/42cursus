# SmoothUX — Editor UI Redesign Plan

## Goal

Rework the left-side editor chrome to feel like a proper tool panel:

- `[+ Add]` pinned in the **top-left corner**, always visible
- Scene object list in the **bottom-left**, scrollable, takes the remaining space
- Clicking `[+ Add]` opens a **centered modal popup** for shape/mesh selection
- Mesh selection leads to a **two-step sub-flow**: format choice → path input
- DEL button stays, but repositions under the scene list

---

## 1. Layout Diagram (current → target)

### Current

```
┌────────────────────────┐
│  OBJECTS  N            │  ← header
│  [LT] 0                │
│  [SP] 0                │
│  ...  (rows)           │
│  ────────────────────  │
│  [+ Add  v]  [  DEL  ] │  ← crud bar at BOTTOM of left panel
└────────────────────────┘
```

### Target

```
┌────────────────────────┐
│  [+ Add]   [  DEL  ]   │  ← TOP toolbar, always visible
│  ────────────────────  │
│                        │
│  (scene list grows     │
│   here, scrollable)    │
│                        │
│  ────────────────────  │
│  OBJECTS  N            │  ← label just above or inside list header
└────────────────────────┘
```

The scene list takes the space **between the toolbar and the bottom edge** of the panel.

---

## 2. Popup Modal Design

Clicking `[+ Add]` opens a full-screen-dimmed modal centred on the viewport.

### Step 1 — Shape Picker

```
╔═════════════════════════════╗
║  Add Object                 ║
║  ─────────────────────────  ║
║  [ Sphere  ]  [ Plane   ]   ║
║  [ Cylinder]  [ Cone    ]   ║
║  [ Light   ]  [ Mesh  → ]   ║
║  ─────────────────────────  ║
║                  [ Cancel ] ║
╚═════════════════════════════╝
```

- Six buttons in a 2×3 grid.
- Sphere / Plane / Cylinder / Cone / Light → spawn immediately (same logic as
  current `editor_add_*`) and close the modal.
- **Mesh →** advances to Step 2.

### Step 2 — Mesh: Format

```
╔═════════════════════════════╗
║  Add Mesh — Format          ║
║  ─────────────────────────  ║
║       [ OBJ  ]  [ GLB  ]    ║
║  ─────────────────────────  ║
║  [ ← Back ]     [ Cancel ]  ║
╚═════════════════════════════╝
```

- OBJ / GLB set an internal format flag.
- After selecting format → advance to Step 3.

### Step 3 — Mesh: Path Input

```
╔═════════════════════════════╗
║  Add Mesh — Path (OBJ)      ║
║  ─────────────────────────  ║
║  > maps/obj/armor/armor.obj_║
║  ─────────────────────────  ║
║  [ ← Back ] [Load] [Cancel] ║
╚═════════════════════════════╝
```

- A single editable text field (captures keyboard input while modal is open).
- `[Load]` validates the path exists, then calls the appropriate loader
  (`editor_add_obj` / `editor_add_glb`) and closes the modal.
- `[← Back]` returns to Step 2.
- Error feedback shown inline if path is bad (red tint + "File not found").

---

## 3. State Machine

Add an enum and fields to `t_crud_ui` in `gui.h`:

```c
typedef enum e_popup_step
{
    POPUP_NONE = 0,   // modal closed
    POPUP_SHAPE,      // step 1: shape picker
    POPUP_MESH_FMT,   // step 2: OBJ vs GLB
    POPUP_MESH_PATH,  // step 3: path text input
}   t_popup_step;

typedef enum e_mesh_fmt
{
    MESH_FMT_OBJ,
    MESH_FMT_GLB,
}   t_mesh_fmt;

typedef struct s_crud_ui
{
    t_popup_step    popup;            // current modal step
    t_mesh_fmt      mesh_fmt;         // chosen format (step 2 → 3)
    char            path_buf[512];    // typed path (step 3)
    int             path_len;         // cursor position / length
    bool            path_error;       // true → show red error tint
}   t_crud_ui;
```

`add_open` is **removed** — replaced by `popup != POPUP_NONE`.

---

## 4. Files to Create / Modify

| File | Change |
|---|---|
| `includes/gui.h` | Replace `t_crud_ui` with new struct above; add `t_popup_step`, `t_mesh_fmt` enums |
| `includes/editor.h` | Add constants: `POPUP_W 360`, `POPUP_ITEM_H 34`, `POPUP_PAD 16`; remove `CRUD_ADD_W` |
| `srcs/gui/editor/crud_ui.c` | **Rewrite** — layout functions for the new top toolbar (no dropdown); draw/click wrappers now just toggle `popup = POPUP_SHAPE` |
| `srcs/gui/editor/popup.c` | **New file** — draw + click logic for all three popup steps |
| `srcs/gui/editor/scene_panel.c` | Move list Y-origin from `48` to just below the new toolbar (`CRUD_PANEL_H + 8`); extend scroll region down to `disp_h`; move label to top of list area |
| `srcs/gui/input/keyboard/handlers.c` | While `popup == POPUP_MESH_PATH`: send key events to `path_buf` instead of camera; Backspace removes last char; Return fires Load |
| `srcs/gui/render/overlay/panel.c` (or new draw call in `render.c`) | Draw dim overlay + modal on top of everything when `popup != POPUP_NONE` |
| `srcs/gui/editor/crud.c` | Add `editor_add_obj(t_gui *, const char *path)` and `editor_add_glb(t_gui *, const char *path)` stubs that call existing loaders |

---

## 5. Drawing Order

Currently: bg → tiles → overlay → scene panel text → crud buttons

New order (same pipeline, add one step at the end):

```
bg → tiles → overlay → scene panel bg → scene list → top toolbar → [popup dim + modal]
```

The modal is drawn last so it sits on top of everything. The dim is a
semi-transparent full-screen black rectangle (`alpha ≈ 0.55`) drawn via the
existing `draw_panel` / `color_blend` path.

---

## 6. Keyboard Capture While Modal Open

When `popup == POPUP_MESH_PATH`:

- **All printable ASCII** → appended to `path_buf` (up to 511 chars).
- **Backspace (`XK_BackSpace`)** → `path_len--`, clear `path_error`.
- **Return (`XK_Return`)** → attempt load (same as `[Load]` click).
- **Escape (`XK_Escape`)** → `popup = POPUP_NONE`.
- **Camera / movement keys are suppressed** while the modal is open.

This is done by checking `gui->crud.popup != POPUP_NONE` at the top of the
keyboard handler dispatch and short-circuiting into the path-input handler
instead.

---

## 7. Load Validation

Before calling the loader:

1. Check `path_buf[0] != '\0'`.
2. Check file exists: `access(path_buf, R_OK) == 0`.
3. If either fails → set `path_error = true`, return without closing modal.
4. On success → call `editor_add_obj` or `editor_add_glb`, reset `crud` state,
   close modal.

---

## 8. Implementation Order

1. `gui.h` — new `t_crud_ui` + enums  
2. `editor.h` — new constants  
3. `scene_panel.c` — move list origin to below top toolbar  
4. `crud_ui.c` — rewrite toolbar (top position, no dropdown)  
5. `popup.c` — new file: draw + click for all 3 steps  
6. `keyboard/handlers.c` — path capture while popup open  
7. `crud.c` — `editor_add_obj` / `editor_add_glb`  
8. Wire popup draw call into render loop (after all other overlays)  
9. Compile + manual test each step  
10. Commit  
