# Events Module

Handles runtime input and window events. This subtree is responsible for creating the event context, registering MLX hooks, updating keyboard and mouse state, reacting to one-shot key commands, processing continuous movement and rotation, and handling resize and FPS updates.

---

## Directory Structure
- `srcs/events/` — Events root
- `init/` — Event object creation, hook registration, and loop processing
- `keys/` — Key dispatch tables and key handlers
- `mouse/` — Mouse press, release, move, and scroll handlers
- `gui/` — Window resize and FPS utilities

---

## How It Works

### Global Pipeline
1. `init_events` allocates one `t_events` object and copies the shared runtime pointers into it.
2. `setup_hooks` registers close, key, mouse, resize, and loop callbacks with MLX.
3. Key presses are routed through the key-action table and may redraw immediately for one-shot actions.
4. Held movement and rotation flags are processed from `loop_hook` every frame.
5. Mouse gestures update camera rotation, color shift, dampening, and zoom.
6. Resize handling rebuilds images and recenters the camera.
7. FPS sampling updates the frame-data counters used by the GUI.

---

## Developer Notes
- The events layer is the bridge between raw MLX callbacks and higher-level camera, graphics, and GUI state.
- One-shot actions usually return `1` so the caller can trigger an immediate redraw.
- Continuous actions store state in `events->keys` or `events->mouse` and are consumed from `loop_hook`.

For exported declarations, see `includes/events.h`.