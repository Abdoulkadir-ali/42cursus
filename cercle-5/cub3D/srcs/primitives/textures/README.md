# 🖼️ Texture Subsystem (`srcs/primitives/textures`)

![Subsystem](https://img.shields.io/badge/Subsystem-Asset_Management-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Detailed-success?style=for-the-badge)

---

## 🚧 Subsystem Boundary
> [!NOTE]
> **Trigger:** Activated during initialization to load environment textures and sprites defined in the `.cub` file.
> 
> **Output:** Provides a high-speed pixel lookup interface for the rendering engine, bypassing standard MLX image overhead for core raycasting.

---

## ✅ Responsibilities & ❌ Anti-Responsibilities
- **Must:** Parse XPM file headers and color tables manually for direct pixel access.
- **Must:** Cache loaded textures to prevent redundant disk I/O.
- **Must:** Provide UV-mapped pixel retrieval for wall and sprite rendering.
- **Must:** Handle transparency in XPM files via alpha-channel simulation.
- **Must Not:** Handle raycasting math (delegated to `engine/`).
- **Must Not:** Draw directly to the screen (delegated to `window/`).

---

## 🔄 Asset Pipeline
```mermaid
graph LR
    A[XPM File] --> B[Header Parser]
    B --> C[Color Table Builder]
    C --> D[Pixel Buffer Allocation]
    D --> E[Texture Cache]
    E --> F[Rendering Engine]
```

---

## 💾 Memory Contracts (Critical)
| Function Allocates | Freeing Responsibility | Condition |
| :--- | :--- | :--- |
| `load_xpm()` | `free_texture()` | Raw pixel buffers and color tables must be freed during cleanup. |
| `init_cache()` | `clear_cache()` | The global texture cache must be emptied during `safe_exit`. |

---

## 🧬 Texture Optimization Matrix
| Feature | Implementation | Notes |
| :--- | :--- | :--- |
| **Direct Access** | Manual XPM decoding | Allows O(1) pixel lookup without MLX overhead. |
| **Caching** | Pointer-based registry | Prevents reloading shared textures (e.g., repeating wall segments). |
| **Translucency** | Alpha-thresholding | Supports 1-bit transparency for sprites and decals. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Invalid XPM Format:** The manual parser expects standard XPM3 formatting. Malformed files must be trapped early in `header.c` to prevent buffer overflows during pixel decoding.

---

## 🗂️ Files Inventory
| File | Primary Function | Role |
| :--- | :--- | :--- |
| `xpm.c` | `load_xpm()` | Entry point for loading assets into the engine. |
| `dxpm.c` | `decode_xpm()` | Direct XPM decoder for optimized pixel access. |
| `header.c` | `parse_header()` | Validates dimensions and color counts from XPM files. |
| `table.c` | `build_table()` | Manages color mapping and transparency indexes. |
| `cache.c` | `get_cached_tex()` | Global registry for reusable texture assets. |
