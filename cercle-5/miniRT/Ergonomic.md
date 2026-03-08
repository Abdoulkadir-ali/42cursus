# Ergonomic UI Improvement Plan

---

## Deep Analysis — Current State

### Structural Issues

| Area | Root Problem |
|---|---|
| **Ambient stomp bug** | `update_ambient()` in `loop.c` runs every frame and overwrites `scene->ambient.rgb` from the legacy `gui->ambient_intensity` / `gui->ambient_color` fields — making the new inspector sliders for ambient appear to have no effect the next frame |
| **Camera rotation on panel click** | In `buttons.c`, `cam_ctrl.mouse_left_pressed = true` is set unconditionally after UI dispatch — so clicking a slider or scene row also activates camera orbit |
| **No modal input separation** | There is no "camera mode" vs "editor mode" concept; LMB does camera orbit AND object pick simultaneously |
| **Legacy help text on viewport** | `draw_ui_help` draws WASD/LMB hints at `x=SCENE_PANEL_W+16, y=38` directly on the rendered image with no panel behind it |
| **`draw_ui_object` hardcoded to mesh[0]** | Always shows mesh[0] info at `(350,38)` regardless of what is selected — needs to either reflect selection or be removed |
| **Legacy bottom bar duplicates inspector** | The 460×56 bottom panel shows camera POS/ROT already visible in the inspector's Transform tab |
| **Duplicate ambient controls** | `[/]` keys, `R/G/B` keys, inspector sliders, and status text overlay all control/show ambient — now reduced: `[/]` and `R/G/B` removed (Phase E5 done), sliders are canonical |
| **`draw_ui_status` duplicates sliders** | Status overlay prints ambient intensity + color hex that the inspector already shows with interactive sliders |

### UX Issues

| Area | Problem |
|---|---|
| CRUD bar | 5 raw `+SP / +PL / +CY / +CO / +LT` buttons crammed in two rows — not discoverable |
| Delete | Only mouse click on DEL button — no `Delete` key shortcut |
| Scene panel header | Scrollable list has no column header or title; no empty-state message |
| Inspector tabs | Active tab has same visual weight as inactive — no underline/accent indicator |
| Escape | Exits the app immediately — should first deselect, then quit |
| Selection feedback | No persistent row highlight in scene panel while inspector is open |
| No render scale indicator | User doesn't know they're in draft / tile mode |

---

## Bugs Fixed

### ✅ R/G/B / `[/]` Legacy Ambient Keys Removed (done)
`srcs/gui/input/keyboard/handlers.c` — those blocks are gone.  
Canonical control is the inspector Ambient panel sliders.

### ⚠️ Ambient Stomp Bug (not yet fixed — must fix for sliders to work)

**Problem:** `update_ambient()` in `srcs/gui/render/loop.c` runs every frame:
```c
static void update_ambient(t_gui *gui)
{
    /* converts gui->ambient_intensity + gui->ambient_color → scene->ambient.rgb */
}
```
This overwrites whatever the Ambient sliders wrote to `scene->ambient.rgb`.

**Fix:** Remove `update_ambient()` or the call to it. The inspector sliders now own `scene->ambient.rgb` and `scene->ambient.brightness` directly. The legacy `gui->ambient_intensity` / `gui->ambient_color` fields are only used for:
1. The initial value set in `gui_init` (now also snapshotted via `scene_snap`)
2. The now-removed `[/]` / `R/G/B` key handlers

**Files to change:** `srcs/gui/render/loop.c` — delete the `update_ambient` function and its call from `render_loop`.

### ⚠️ Camera Rotation on Panel Click (not yet fixed)

**Problem:** `srcs/gui/input/mouse/buttons.c` sets `cam_ctrl.mouse_left_pressed = true` even after a UI click is handled.

**Fix:** Return early from the camera-press path if `inspector_handle_click` or `scene_panel_handle_click` returned `true`.

---

## Phase R — Scene Reset with `R` Key ✅ DONE

**Goal:** Press `R` to restore the scene to its exact post-parse state, per-map.

### Architecture

A proper **map manager** now owns all scene lifetime. Each map entry carries its own snapshot, eliminating the old single `gui->scene_snap` tied to the initial scene.

```
t_map_entry {
    char        *path;     /* "maps/rt/foo.rt"  */
    t_scene     *scene;    /* NULL = not yet parsed */
    t_scene_snap snap;     /* pristine post-parse state */
    t_map_entry *next;
}

s_map {
    t_map_entry *head;     /* linked list of all discovered maps */
    t_map_entry *current;  /* active entry */
    int          count;
}
```

### Snapshot lifecycle
- **First visit to a map** → parse + BVH build + `scene_snap_take`.
- **Subsequent visits** → cached scene reused, no reparse, no snap (already taken).
- **`R` key** → `scene_reset` reads from `gui->map_info.current->snap`.
- **Map switch** → `gui->scene = next_entry->scene`; camera + selection reset.

### What is snapshotted (per map)
- All sphere / plane / cylinder / cone / light arrays (POD memcpy)
- Full materials array (texture image pointers are session-lifetime, safe to share)
- Per-mesh editable fields: `transform`, `mat_id`, `phys`
- `scene->ambient`, `scene->camera`
- Legacy `gui->ambient_intensity`, `gui->ambient_color`

### Ownership / cleanup
- All scene lifetimes owned by the map manager.
- `gui_destroy` → `map_manager_destroy` walks the list, frees snaps, destroys scenes, frees paths.
- `main.c::cleanup` calls `destroy_scene(scene)` only when `gui` is NULL (init failed before the map manager took ownership).

### Files changed
| File | Change |
|---|---|
| `includes/gui.h` | Added `t_map_entry` struct; `s_map` → `{head, current, count}`; removed `scene_snap` from `s_gui`; updated prototypes |
| `srcs/gui/map/files.c` | `fill_map_list` builds linked list of `t_map_entry`; removed `count_maps` |
| `srcs/gui/map/current.c` | Rewritten as `set_current_entry` — finds matching entry, stores initial scene, takes snap |
| `srcs/gui/map/init.c` | `gui_map_switcher_init` uses linked list; no `calloc` for file array |
| `srcs/gui/map/load.c` | `map_load_entry` — parses + caches on first visit, reuses on subsequent visits |
| `srcs/gui/map/next.c` | `gui_next_map` traverses linked list; wraps to head; calls `clear_selection` |
| `srcs/gui/map/destroy.c` | New — `map_manager_destroy` frees entire cache |
| `srcs/gui/render/init.c` | Removed per-gui snap call; `gui_destroy` uses `map_manager_destroy` |
| `srcs/gui/editor/scene_reset.c` | `scene_reset` reads `gui->map_info.current->snap` |
| `srcs/core/main.c` | `cleanup` uses `else if (scene)` to avoid double-free |
| `srcs/debug/print/system/gui.c` | Updated debug print for new `s_map` shape |
| `srcs/gui/input/keyboard/handlers.c` | `XK_r → scene_reset(gui)` |

---

## Phase E1 — DEL Shortcut (small, immediate)

**Goal:** Press `Delete` or `BackSpace` to delete the selected object.

### Files to change
- `srcs/gui/input/keyboard/handlers.c` — add `XK_Delete` and `XK_BackSpace` entries in the keymap dispatch, calling `editor_delete_selected(gui)` when `gui->selection.active`.
- `srcs/gui/input/keyboard/misc.c` — add `void delete_selected_press(t_gui *gui)` wrapper.

### Behaviour
- If nothing is selected → key is silently ignored.
- After delete → selection cleared, inspector hidden, render dirtied.
- If a dropdown is open → `Escape` closes it first (see Phase E2).

---

## Phase E2 — "Add Object" Dropdown (medium)

**Goal:** Replace the 5 raw `+XX` buttons with a single `+ Add` button that opens a dropdown menu.

### New UI element: `t_dropdown`

```c
typedef struct s_dropdown {
    bool        open;       /* is dropdown visible right now? */
    int         x;          /* anchor top-left x */
    int         y;          /* anchor top-left y */
    int         item_w;     /* item width (= SCENE_PANEL_W - 8) */
    int         item_h;     /* per-item row height (22 px) */
    int         count;      /* number of items */
} t_dropdown;
```

Add `t_dropdown add_dropdown` to `t_gui` (inside `gui.h`).

### Layout

```
[ + Add   ] [ DEL ]          ← bottom of scene panel, 1 row only
      ↑
  ┌─────────────┐
  │  Sphere     │
  │  Plane      │
  │  Cylinder   │
  │  Cone       │
  │  Light      │
  └─────────────┘
  (draws upward from the button)
```

### Files to create / change
- **`srcs/gui/editor/dropdown.c`** (new) — `draw_dropdown`, `dropdown_handle_click`, `dropdown_close`.
- **`srcs/gui/editor/crud_ui.c`** — remove old 5-button row; draw single `+ Add` button + `DEL` in one row; call `draw_dropdown` when `gui->add_dropdown.open`.
- **`includes/editor.h`** — add `t_dropdown` struct + prototypes.
- **`includes/gui.h`** — add `t_dropdown add_dropdown` field to `t_gui`.
- **`srcs/gui/editor/scene_panel.c` / `editor_init`** — zero-initialise `add_dropdown`.
- **`srcs/gui/input/mouse/buttons.c`** — in `mouse_click`, call `dropdown_handle_click` before other checks; clicking anywhere outside the open dropdown closes it.
- **`srcs/gui/input/keyboard/handlers.c`** — `Escape` first closes dropdown if open, else clears selection, else exits.

### Behaviour
- Single left-click on `+ Add` toggles dropdown open/closed.
- Clicking an item calls the appropriate `editor_add_*` and closes the dropdown.
- Clicking anywhere outside the dropdown → close.
- Dropdown draws on top of everything (last draw call in overlay).

---

## Phase E3 — Scene Panel Polish (small)

**Goal:** Make the scene list feel more like a proper panel.

### Changes
- **Header row** — draw a fixed `OBJECTS` label + object count in a styled header bar at the top of the scene panel (y = 0..36), not scrollable.
- **Selected row highlight** — currently the highlight only shows on hover. When an object is selected and the inspector opens, keep its row in `COL_ROW_SEL` colour permanently.
- **Empty-state message** — if `count_scene_rows == 0`, draw `"No objects — use + Add"` centered in the panel.
- **Separator before CRUD area** — already exists, make it 1 px taller for visual clarity.

### Files to change
- `srcs/gui/editor/scene_panel.c`

---

## Phase E4 — Inspector Tab Visual Improvement (small)

**Goal:** Make the active tab clearly stand out.

### Changes
- Draw a filled accent-coloured underline bar (3 px) under the active tab label instead of just changing text colour.
- Inactive tabs: `COL_TEXT` (dimmed).
- Active tab: `COL_ACCENT` text + a `3 px` filled rect beneath the text at `y = 76..79`.

### Files to change
- `srcs/gui/editor/inspector.c` — `draw_inspector_tabs`.
- `srcs/gui/render/overlay/panel.c` — expose a `draw_hline(gui, x, y, w, color)` helper if not already present.

---

## Phase E5 — Keyboard Shortcut Cleanup ✅ DONE

The legacy `R/G/B/[/]` ambient key handlers have been removed from  
`srcs/gui/input/keyboard/handlers.c`. The inspector Ambient panel sliders are  
the canonical interface. `P` (physics) and `F` (full-res) are kept.

---

## Phase E6 — Escape Key Hierarchy (small)

**Goal:** Make `Escape` contextual instead of always quitting.

### New priority chain (checked in order)
1. Dropdown open → close dropdown.
2. Selection active → deselect + close inspector.
3. Nothing else pending → quit (current behaviour).

### Files to change
- `srcs/gui/input/keyboard/misc.c` — rewrite `exit_press` to check `gui->add_dropdown.open` then `gui->selection.active`.

---

## Phase E7 — "F2 Rename" for Mesh Info Panel (future / optional)

**Goal:** Allow renaming a mesh from the Info tab via a text input.

> MiniLibX has no native text-input widget. This would require building a simple inline text buffer + cursor, rendered with `mlx_string_put`. Defer until Phases E1–E6 are stable.

---

## Implementation Order

| Phase | Status | Effort | Commit tag |
|---|---|---|---|
| R Scene reset (`R` key) | ✅ done | S | `feat(editor): R key resets scene to post-parse state` |
| E5 Keyboard cleanup | ✅ done | XS | (merged into R commit) |
| Fix ambient stomp bug | ⚠️ must-fix | XS | `fix(loop): remove update_ambient, sliders own ambient` |
| Fix camera on panel click | ⚠️ must-fix | XS | `fix(input): LMB camera only when UI did not handle click` |
| E1 DEL shortcut | not started | XS | `feat(input): DEL/BackSpace deletes selected object` |
| E6 Escape hierarchy | not started | XS | `fix(input): Escape is contextual (dropdown→deselect→quit)` |
| E3 Scene panel polish | not started | S | `feat(ui): scene panel header, selection highlight, empty state` |
| E4 Inspector tab bar | not started | S | `feat(inspector): accent underline for active tab` |
| E2 Add dropdown | not started | M | `feat(crud): + Add dropdown replaces raw type buttons` |
| E7 Rename text input | deferred | L | defer |

---

## Notes & Constraints

- **42 Norm**: all new functions ≤ 25 lines, ≤ 4 params, no VLAs.
- **No heap for UI state**: `t_dropdown` is a fixed struct inside `t_gui` — no malloc.
- **MiniLibX limitation**: no native z-order; dropdown must be drawn last in the overlay loop to appear on top.
- **Dropdown closes on render**: the dropdown's `open` flag is checked each frame; animation isn't feasible without delta-time rendering — open/close is instant.
