# Fixing.md — Bug Fixes & Feature Additions

Eight targeted fixes derived from live testing. Files and functions are exact.
Fixes are ordered by dependency: F1+F7 share a key reassignment and must be done
together. F6 and F8 both touch `text.c` and are easiest to do in one pass.

---

## F1 — Physics toggle uses `P` but display shows `[ X ]`

### Problem
`handlers.c` toggles `gui->physics_enabled` on `XK_p / XK_P`.
`draw_ui_status` in `text.c` renders `"[ X ] Simulate Physics"` where `X` is
just the checkbox content — not a keybind.  The user reads `X` as a keybind.

### Decision
Move physics toggle to **X** key. `P` is freed for previous-map (F7).
This makes the display `[ X ] Simulate Physics` actually correct.

### Changes

**`srcs/gui/input/keyboard/handlers.c`**
```c
// Replace:
if (keycode == XK_p || keycode == XK_P)

// With:
if (keycode == XK_x || keycode == XK_X)
```

**`srcs/gui/render/overlay/text.c`** — update the help line to mention `X`:
```c
// In draw_ui_help, change the speed/nextmap line:
"[ X ] Physics   N / P           Next / Prev map"
```

**`srcs/gui/input/keyboard/handlers.c`** — ensure `XK_p` is *not* in the
physics block anymore so it routes into `key_release` path for prev-map (see F7).

---

## F2 — Roughness / Metallic have no visual effect; rename IOR slider

### Problem (roughness / metallic)
`calc_light` in `light.c` computes Blinn-Phong using only `mat.shininess` and
`mat.specular`.  `setup_shading` in `compute.c` writes `ctx->mat.roughness` and
`ctx->mat.metallic` but `calc_light` never reads them.  Changing the sliders has
zero visual effect.

### Fix — map into Blinn-Phong parameters
In **`srcs/rays/raytracing/postprocess/shading/compute.c`**, at the end of
`setup_shading`, after the roughness / metallic values are loaded:

```c
// After: ctx->mat.roughness = ...  and  ctx->mat.metallic = ...
// Add these two lines to wire roughness/metallic into the lighting equation:
ctx->mat.shininess = pow(1.0 - ctx->mat.roughness, 4.0) * 200.0 + 2.0;
ctx->mat.specular  = ctx->mat.specular * (1.0 - ctx->mat.metallic * 0.5)
                   + ctx->mat.metallic * 0.9;
```

Rationale:
- `roughness = 0` → shininess ≈ 202 (tight specular), `roughness = 1` → shininess ≈ 2 (fully diffuse).
- `metallic = 1` blends `specular` toward 0.9 (metals are highly reflective), `metallic = 0` leaves it unchanged.

No changes to `calc_light` itself — it reads `ctx->mat.shininess` and
`ctx->mat.specular` which are now driven by the PBR sliders.

### Problem (IOR → Refraction Angle)
The slider in `material_panel.c` is labeled `"IOR"` with range `SL_IOR_MIN=1.0`
to `SL_IOR_MAX=3.0`. The user wants `"Refraction Angle"` in degrees `0–180`.
The refraction code in `compute.c` calls `vec3_refract` which expects the
refractive index (a ratio), not an angle.  A conversion is needed.

### Fix — rename label, new range, add angle→IOR conversion
**`srcs/gui/editor/material_panel.c`** — in `build_mat_sliders`:
```c
// Replace:
sl[i++] = (t_islider){"IOR", SL_IOR_MIN, SL_IOR_MAX, &mat->refract_index};

// With:
sl[i++] = (t_islider){"Refr Angle", 0.0, 180.0, &mat->refract_angle_deg};
```

Add `double refract_angle_deg` to `t_material` in **`includes/surface.h`**
(or reuse an existing unused field), or:

**Alternative (no new field)**: Keep `mat->refract_index` as the stored value
in degrees (0–180), convert to IOR in `compute.c` just before calling
`vec3_refract`:
```c
// In compute.c, before using mat.refract_index in vec3_refract:
double ior = 1.0 + (mat.refract_index / 180.0) * 2.0; // maps 0°→1.0, 180°→3.0
// Then pass ior to vec3_refract instead of mat.refract_index
```

This avoids adding a new field; the stored value becomes degrees and the
conversion happens at shading time.  Update `SL_IOR_MIN/MAX` defines in
**`includes/editor.h`** to `0.0 / 180.0`.

---

## F3 — Scale slider does not resize spheres

### Problem
`transform_panel.c:build_tr_sliders` sets:
```c
sl[i++] = (t_islider){"Scale", SL_SCALE_MIN, SL_SCALE_MAX, &tr->scale.x};
```
The slider writes `transform.scale.x`. But `intersect_sphere` in
`srcs/rays/raytracing/intersection/sphere/intersect.c` computes:
```c
q.c = vec3_dot(oc, oc) - sp->radius_sq;   // uses radius_sq, NOT scale.x
```
`radius_sq` is a cached field set once at parse time and never updated by the
editor. Dragging the Scale slider silently writes `scale.x` but the ray-sphere
math never sees it.

The same issue applies to `inv_transform` used by the deformed-sphere path.

### Fix — add `on_change` callback to `t_islider`

**`includes/editor.h`** — extend `t_islider`:
```c
typedef struct s_islider
{
    const char      *label;
    double           min;
    double           max;
    double          *ptr;
    void           (*on_change)(struct s_gui *gui);   // NEW — NULL = no-op
}   t_islider;
```

**`srcs/gui/editor/slider_inline.c`** — at the point where the dragged value is
written to `*state->value_ptr`, add:
```c
// After writing the new value:
if (sl.on_change)
    sl.on_change(gui);
```

**`srcs/gui/editor/transform_panel.c`** — add a sync callback and wire it:
```c
static void sphere_scale_sync(t_gui *gui)
{
    t_selection *sel = &gui->selection;
    t_sphere    *sp;

    if (!sel->active || sel->type != TYPE_SPHERE)
        return;
    sp = &gui->scene->spheres[sel->index];
    sp->transform.scale.y = sp->transform.scale.x;
    sp->transform.scale.z = sp->transform.scale.x;
    sp->radius_sq         = sp->transform.scale.x * sp->transform.scale.x;
    /* rebuild inv_transform for deformed path */
    t_mat4 s = mat4_scale(sp->transform.scale);
    sp->inv_transform = mat4_inverse_transform(s);
}
```
Then in `build_tr_sliders`, for TYPE_SPHERE:
```c
sl[i++] = (t_islider){"Scale", SL_SCALE_MIN, SL_SCALE_MAX,
                       &tr->scale.x, sphere_scale_sync};
```
All other sliders keep `NULL` for `on_change` — add `, NULL` to every other
`(t_islider){...}` initialiser in `build_tr_sliders` and `build_mat_sliders`.

---

## F4 — Map switch freezes the screen

### Problem
`gui_next_map` in `srcs/gui/map/next.c` calls `map_load_entry`, which calls
`parse_file` + `bvh_create` synchronously on the mlx event-loop thread.
The entire window freezes until parsing completes.

### Fix — offload parse + BVH to a `pthread`

**`includes/gui.h`** — add a load-job struct and field to `t_gui`:
```c
typedef struct s_map_job
{
    pthread_t       tid;
    t_map_entry    *entry;      // target entry being loaded
    t_gui          *gui;
    bool            done;       // set by thread when finished
    bool            active;     // true while thread is running
}   t_map_job;

// Inside t_gui:
t_map_job   map_job;
```

**`srcs/gui/map/load.c`** — add a threaded variant:
```c
static void *load_thread(void *arg)
{
    t_map_job   *job;
    t_map_entry *entry;

    job   = arg;
    entry = job->entry;
    if (!entry->scene)
    {
        entry->scene = parse_file(entry->path, NULL);
        if (entry->scene)
        {
            entry->snap  = scene_snapshot(entry->scene);
            entry->scene->bvh = bvh_create(entry->scene);
        }
    }
    job->done = true;
    return (NULL);
}

void    map_load_async(t_gui *gui, t_map_entry *entry)
{
    if (gui->map_job.active)
        return;                    // already loading, ignore
    gui->map_job.entry  = entry;
    gui->map_job.gui    = gui;
    gui->map_job.done   = false;
    gui->map_job.active = true;
    pthread_create(&gui->map_job.tid, NULL, load_thread, &gui->map_job);
}
```

**`srcs/gui/render/loop.c`** — poll the job each frame in `render_loop` before
drawing:
```c
static void poll_map_job(t_gui *gui)
{
    t_map_job   *job;

    job = &gui->map_job;
    if (!job->active || !job->done)
        return;
    pthread_join(job->tid, NULL);
    job->active = false;
    if (job->entry && job->entry->scene)
    {
        gui->map_info.current = job->entry;
        gui->scene            = job->entry->scene;
        clear_selection(gui);
        gui->render.dirty     = true;
    }
}
```
Call `poll_map_job(gui)` at the top of `render_loop`.

**`srcs/gui/map/next.c`** — replace the `map_load_entry(gui, ...)` call with
`map_load_async(gui, next_entry)`.

**`srcs/gui/map/prev.c`** (see F7) — same replacement.

**Mutex note**: `parse_file` and `bvh_create` must not touch `gui->scene` or
any mlx function. They write only to the private `t_map_entry`. The swap
happens only in `poll_map_job` on the loop thread, so no mutex is needed for the
swap itself. If `parse_file` or `bvh_create` call `ft_printf` / `write`, that
is safe — they are thread-safe at the OS level.

---

## F5 — Left menu (CRUD + scene panel) not elegant

### Current state
`crud_ui.c`: two rows of 52×22 buttons with cryptic labels (`+SP +PL +CY +CO`
on row 1, `+LT DEL` on row 2) drawn at fixed pixel offsets.
`scene_panel.c`: header is `"SCENE"` at `(12, 24)`, no count, no visual bar.

### Fix — single row `[+ Add ▾]` expand menu + `[DEL]`, polished header

**`includes/editor.h`** — add dropdown state:
```c
typedef struct s_crud_ui
{
    bool    add_open;   // dropdown is expanded
}   t_crud_ui;

// Inside t_gui (or t_inspector):
t_crud_ui   crud;
```

**`srcs/gui/editor/crud_ui.c`** — replace the two-row layout with:

```
┌────────────────────────────────────────┐
│ [+ Add ▾]                    [  DEL  ] │  ← always visible row (y = panel bottom - 28)
│                                        │
│  ○ Sphere   ○ Plane                    │  ← dropdown: only when crud.add_open == true
│  ○ Cylinder ○ Cone                     │
│  ○ Light                               │
└────────────────────────────────────────┘
```

- `[+ Add ▾]` toggles `gui->crud.add_open` on LMB click.
- Clicking any dropdown item creates the object and closes the dropdown.
- `[DEL]` deletes the selected object (same as before).
- Dropdown width = `SCENE_PANEL_W - 4`, each item row height = 22.

**`srcs/gui/editor/scene_panel.c`** — replace the plain `"SCENE"` string with a
filled header bar:

```c
// Draw a filled rect at top of panel as header bar
draw_rect(gui, (t_rect){0, 0, SCENE_PANEL_W, 28}, COL_HEADER);
// Draw "OBJECTS (N)" centred in the bar
snprintf(buf, sizeof(buf), "OBJECTS  %d", total_object_count(gui->scene));
mlx_string_put(gui->win.mlx, gui->win.win, 8, 10, COL_ACCENT, buf);
```

If `gui->scene` is NULL or empty, draw `"  (empty)"` in muted colour instead
of showing zero rows.

---

## F6 — Remove Ambient Intensity / Ambient Color from overlay

### Problem
`draw_ui_status` in `srcs/gui/render/overlay/text.c` currently prints three
lines: physics checkbox, ambient intensity, ambient color. The last two are
noise.

### Fix
Delete the two `snprintf`/`mlx_string_put` blocks for ambient intensity and
ambient color.  Leave only the physics checkbox line (which F8 will restyle).

After the fix `draw_ui_status` contains exactly one `mlx_string_put` call.

---

## F7 — Add previous-map key (`P`)

### Problem
No `gui_prev_map` function exists. `P` key is currently used for physics toggle
(fixed by F1 — physics moves to `X`).

### Fix

**`srcs/gui/map/prev.c`** — new file (or add to `next.c`):
```c
void    gui_prev_map(t_gui *gui)
{
    t_map_entry *entry;
    t_map_entry *prev;

    if (!gui->map_info.head || !gui->map_info.current)
        return;
    if (gui->map_job.active)
        return;                       // already loading
    /* walk list to find entry before current */
    entry = gui->map_info.head;
    prev  = NULL;
    while (entry && entry != gui->map_info.current)
    {
        prev  = entry;
        entry = entry->next;
    }
    if (!prev)
    {
        /* current is head — wrap to tail */
        prev = gui->map_info.head;
        while (prev->next)
            prev = prev->next;
    }
    map_load_async(gui, prev);        // async (see F4)
}
```

**`srcs/gui/input/keyboard/misc.c`** — add:
```c
void    map_prev_press(t_gui *gui)
{
    gui_prev_map(gui);
}
```

**`srcs/gui/input/keyboard/handlers.c`** — wire `XK_p`:
```c
// In get_keymap(), add before the terminator:
{XK_p, map_prev_press, NULL},
{XK_P, map_prev_press, NULL},
```
(Physics is now on `XK_x / XK_X`, no conflict.)

**`srcs/gui/render/overlay/text.c`** `draw_ui_help` — update the hint line:
```c
"+/-   Speed  N / P         Next / Prev map"
```

---

## F8 — Physics status indicator (green / red)

### Problem
`draw_ui_status` shows `"[ X ] Simulate Physics"` in plain `COL_TEXT` color.
User wants a colored / styled indicator ("green or red", "Physic ON/OFF").

### Fix
Replace the single remaining line in `draw_ui_status` (after F6) with a
color-coded badge:

```c
void    draw_ui_status(t_gui *gui, int *y)
{
    int     ox;
    int     color;
    char    buf[64];

    ox = SCENE_PANEL_W + 16;
    if (gui->physics_enabled)
    {
        color = 0x44FF44;               // green
        snprintf(buf, sizeof(buf), "[ X ]  PHYSICS  ON");
    }
    else
    {
        color = 0xFF4444;               // red
        snprintf(buf, sizeof(buf), "[   ]  PHYSICS  OFF");
    }
    mlx_string_put(gui->win.mlx, gui->win.win, ox, *y, color, buf);
    *y += 20;
}
```

The `[ X ]` text stays consistent with F1 (X key = physics toggle).
Color lookup: `0x44FF44` = soft green, `0xFF4444` = soft red — both read well
on the dark overlay background.

---

## Key / Bind Summary After All Fixes

| Key | Action |
|-----|--------|
| `X` | Toggle physics ON / OFF (moved from P) |
| `N` | Next map |
| `P` | Previous map (new) |
| `R` | Reset scene to parse-time snapshot |
| `F` | Full-resolution toggle |
| `Esc` | Quit |
| `WASD/QZ` | Move camera |
| `Space/Shift` | Move up/down |
| `+/-` | FOV zoom |
| `↑/↓` | Speed up/down |

---

## Implementation Order

These fixes can be done in any order except the specified dependencies:

1. **F6** — trivial text deletion, do first to reduce noise in `text.c`
2. **F8** — restyled physics line (same file, do right after F6)
3. **F1** — move physics key (`XK_p` → `XK_x` in `handlers.c`)
4. **F7** — add `gui_prev_map` + P key (requires F1 done first)
5. **F2** — roughness/metallic wiring + IOR rename (self-contained)
6. **F3** — scale callback (self-contained, touch `editor.h`, `slider_inline.c`, `transform_panel.c`)
7. **F4** — async map loading (touch `gui.h`, `load.c`, `loop.c`) — do before or after F7
8. **F5** — UI redesign (most visual churn, save for last)
