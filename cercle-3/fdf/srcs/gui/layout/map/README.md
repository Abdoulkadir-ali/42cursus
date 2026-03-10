# Map Layout

Handles display of the currently active map source. This folder is responsible for showing whether the session is using a loaded file, a generated runtime map, or the fallback test grid.

---

## Directory Structure
- `srcs/gui/layout/map/` — Map information layout
- `map.c` — Current map name and generation state display

---

## How It Works

1. `draw_map_layout` adds the section title and generation hint.
2. It checks whether the current map is still one of the loaded map entries.
3. If not, it formats a generated map label with the current generated id.
4. If a loaded map is active, it displays the current map file path.
5. If no map file is available, it displays `Test Grid`.

---

## Developer Notes
- Generated runtime maps are identified by pointer mismatch against the loaded map list.
- The display uses the map manager’s `current_index`, `count`, and `generated_id` fields.

For exported declarations, see `includes/gui.h`.