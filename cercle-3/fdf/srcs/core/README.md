# Core Module

Handles application bootstrap and shutdown. This folder is responsible for validating startup arguments, creating the MLX window and frame buffers, wiring together the camera, graphics, GUI, and event subsystems, and releasing owned resources on exit.

---

## Directory Structure
- `srcs/core/` — Application bootstrap and teardown
- `cleanup.c` — Resource release and process exit
- `helper.c` — Startup sequencing helpers used by `main`
- `init.c` — Window, image, GUI, and default render setup
- `main.c` — Program entry point and top-level startup pipeline

---

## How It Works

### Global Pipeline
1. `main` validates the command-line shape and initializes X11 threading.
2. `init_data_and_window` validates the target map path, clears the `t_data` aggregate, initializes MLX, creates the window, and allocates the main image plus z-buffer.
3. `init_camera_and_graphics` builds the camera manager from the active map source and allocates the graphics runtime.
4. `init_defaults_and_render` seeds the default render settings, allocates the GUI, binds the current map and camera pointers into the graphics state, and fits the camera to the map.
5. `init_events_and_hooks` creates the event context, installs hooks, triggers the first redraw, and transfers GUI ownership to the events layer.
6. `mlx_loop` takes over the runtime event loop.
7. `cleanup_and_exit` releases loaded maps, cached projections, LOD maps, frame buffers, the MLX window, and the display connection.

---

## File Notes

### cleanup.c
- Frees the map manager’s loaded map list and map-file path list.
- Releases graphics-side cached projections and generated LOD maps.
- Destroys the main image, GUI image, window, display, and z-buffer.

### helper.c
- Groups startup into reusable stages so `main` stays linear.
- Contains the argument and path validation helper used before window setup.

### init.c
- Creates the main MLX image and z-buffer.
- Initializes the GUI and binds runtime pointers between subsystems.

### main.c
- Orchestrates the startup stages in order and enters the MLX event loop.

---

## Developer Notes
- `check_args_and_map` still supports a default directory branch, but the current `main` entry point requires exactly one explicit path argument, so that branch is not reached through normal execution.
- Ownership of `data->gui` is handed off to the event layer after `init_events_and_hooks` succeeds.

For exported declarations, see `includes/core.h`.