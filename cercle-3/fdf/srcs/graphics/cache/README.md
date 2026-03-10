# Cache Module

Handles precomputed screen-space projections of map points. This folder is responsible for allocating the projection cache, invalidating it when the map or camera changes, filling it in parallel, and providing a safe fallback when cached points are unavailable.

---

## Directory Structure
- `srcs/graphics/cache/` — Projection cache helpers
- `cache.c` — Cache invalidation and refresh control
- `helper.c` — Cache allocation and threaded filling
- `fallback.c` — Cache lookup fallback to direct transforms

---

## How It Works

1. `cache_projections` checks whether the current cache can be reused.
2. If camera or map state changed, it refreshes the camera matrices and calls `init_cache`.
3. `fill_cache` splits map rows across threads and transforms each row into cached `t_point` values.
4. `get_cached_proj` returns a cached point when valid or computes a direct fallback projection when needed.

---

## Developer Notes
- The cache stores transformed `t_point` values, not just positions.
- Camera state is copied into `g->cache.cam_state` so invalidation stays local to the graphics layer.

For exported declarations, see `includes/graphics.h`.