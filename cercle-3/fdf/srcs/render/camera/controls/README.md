# Camera Controls Module

Handles runtime camera fitting, recentering, style reset, and smooth zoom updates. This subsystem is responsible for mutating `t_camera` and `t_camera_manager` state in response to map changes, window changes, and interactive input.

---

## Directory Structure
- `srcs/render/camera/controls/` — High-level camera control helpers
- `adjust.c` — Fit and center the camera against the active map
- `center.c` — Preserve visual centering when the window size changes
- `reset_style.c` — Reset camera color styling to its neutral state
- `zoom.c` — Zoom target changes and smooth zoom interpolation
- `rotate/` — Rotation-matrix construction and vector rotation helpers

---

## How It Works

### Global Pipeline
1. The core startup code finishes map and graphics setup.
2. `init_and_render` calls `adjust_camera_to_map` to place the first view.
3. Map-switch and regenerate actions can call `center_camera_on_map` to refit the active terrain.
4. Resize handling can call `recenter_camera_on_resize` to keep the image visually centered after the window geometry changes.
5. Mouse wheel and key handlers update zoom targets through `zoom_in` and `zoom_out`.
6. The loop hook calls `update_zoom` every iteration to smoothly move `scale` toward `target_scale`.
7. Style toggles can call `reset_style` to clear accumulated color shifts.

### `adjust.c`
- Owns the logic for fitting a map into the available viewport.
- Computes both the scale and the camera offsets needed to center the scene.

#### Pipeline Inside `adjust.c`
1. `adjust_camera_to_map` first validates that both the manager and the active map exist.
2. It computes an ideal scale through `calculate_ideal_zoom`.
3. `calculate_ideal_zoom` chooses the larger map dimension as the fitting reference.
4. It computes horizontal and vertical candidate scales from the current window size.
5. It clamps the chosen scale between `DEFAULT_ZOOM_MIN` and `DEFAULT_ZOOM_MAX`.
6. `adjust_camera_to_map` writes that value into both `scale` and `target_scale`.
7. It restores the default camera angles through `set_ideal_angle`.
8. It computes a centered screen offset through `calculate_ideal_position`.
9. It rebuilds `grid_center` from the map width, height, and z-range.
10. It resets `dampening_threshold` and `alpha` for a predictable initial view.

### `center_camera_on_map`
- Refits the current map without reapplying the full default angle setup.
- Useful when the active map changes after startup.

#### Pipeline Inside `center_camera_on_map`
1. Recomputes the map-space center from width, height, and z-range.
2. Recomputes the ideal scale.
3. Copies the new scale into both `scale` and `target_scale`.
4. Clears dampening by writing `0.0` into `dampening_threshold`.
5. Restores `z_scale` to `1.0`.
6. Recomputes the screen offset through `calculate_ideal_position`.

### `center.c`
- Contains a single helper, `recenter_camera_on_resize`.
- It does not refit the map; it only shifts the current camera offset by half of the window size delta.
- This keeps the existing framing visually centered when the window grows or shrinks.

### `reset_style.c`
- Contains `reset_style`.
- It clears `camera->color_shift` back to zero on all three channels.
- It does not touch projection, scale, or rotation data.

### `zoom.c`
- Owns zoom target manipulation and the smoothing step used by the event loop.

#### Pipeline Inside `zoom.c`
1. `zoom_in` computes a multiplicative factor from `zoom_speed`.
2. It multiplies `target_scale` by that factor.
3. It clamps `target_scale` to a hard maximum of `100`.
4. `zoom_out` computes the inverse-style factor from the same `zoom_speed` field.
5. It multiplies `target_scale` downward without an explicit lower clamp in this function.
6. `update_zoom` runs every loop iteration.
7. It computes the difference between `target_scale` and `scale`.
8. If the difference is nearly zero, it snaps `scale` to `target_scale`.
9. Otherwise it advances `scale` by `15%` of the remaining distance.

### Runtime Handoff
1. This folder mutates user-facing camera state.
2. The render cache and projection code consume that state later in the frame.
3. Rotation-matrix refresh and vector rotation helpers live in the nested `rotate/` submodule.
4. The event system is the main caller for the zoom, refit, and recenter helpers.

---

## Developer Notes
- `adjust.c` is map-aware and window-aware.
- `center.c` is window-aware only.
- `zoom.c` separates target updates from the smoothing step so user input stays responsive while motion remains stable.
- `reset_style.c` is intentionally narrow and only resets color styling state.

For the low-level rotation helpers used by this folder and the wider render pipeline, see `rotate/README.md`.