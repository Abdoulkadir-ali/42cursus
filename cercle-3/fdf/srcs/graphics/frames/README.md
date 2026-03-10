# Frame Module

Handles frame buffer reset work before each render pass. This folder is responsible for clearing the main image and resetting the z-buffer when depth culling is active.

---

## Directory Structure
- `srcs/graphics/frames/` — Frame buffer helpers
- `clear.c` — Main image and z-buffer clearing

---

## How It Works

1. `clear_frame_buffers` checks which buffers are active.
2. `clear_image` zeroes the main MLX image.
3. `clear_z_buffer` resets each depth entry to a large sentinel value.

---

## Developer Notes
- The z-buffer is only touched when depth culling is enabled.

For exported declarations, see `includes/graphics.h`.