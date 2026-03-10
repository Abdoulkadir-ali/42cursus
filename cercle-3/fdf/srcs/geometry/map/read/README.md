# Geometry Map Read

## Directory Structure

- `select.c`: initialize the map list and choose fallback behavior.
- `file.c`: filesystem filters and the thread entry routine.
- `thread.c`: spawn and join map-loading threads.
- `loader.c`: load one map file into a finalized `t_map`.
- `parser.c`: compute dimensions, allocate arrays, and read lines.
- `helper.c`: token parsing helpers for heights and inline colors.
- `cycle.c`: rotate through the loaded map set.

## How It Works

The reader enumerates `.fdf` files in the configured directory, launches worker
threads to load them, and stores the resulting `t_map` pointers in `t_maps`.
Each file is parsed in two passes: one to measure width and height, then one to
fill point arrays with z values and optional colors.

## Developer Notes

- Empty or unreadable map sets fall back to `create_test_grid()`.
- The parser keeps source colors separate so later style changes can restore raw
  imported colors.