# Format Helpers

Handles lightweight conversion of runtime numbers into short GUI strings. This folder is responsible for producing fixed-size display text for speeds, floats, signed integers, and unsigned integers.

---

## Directory Structure
- `srcs/gui/print/format/` — Numeric GUI formatting helpers
- `format.c` — Speed and float formatting
- `nbr.c` — Integer formatting and digit reversal

---

## How It Works

1. Higher-level GUI sections allocate small stack buffers.
2. Format helpers write ASCII digits directly into those buffers.
3. Integer helpers build digits in reverse order and then correct them with `reverse_digits`.
4. The finished string is passed to the print helpers for display.

---

## Developer Notes
- These helpers assume the caller provides a sufficiently large output buffer.
- Integer formatting avoids heap allocation and `printf`-style dependencies.

For exported declarations, see `includes/gui.h`.