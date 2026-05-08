# ⚙️ Engine Core (`srcs/engine`)

![Subsystem](https://img.shields.io/badge/Subsystem-Core_Engine-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Detailed-success?style=for-the-badge)

---

## 🚧 Subsystem Boundary
> [!NOTE]
> **Trigger:** Orchestrated by `core/main.c`, this subsystem drives the entire game lifecycle through the MLX loop hooks.
> 
> **Output:** A fully processed and rendered game frame, incorporating physics resolution, entity animations, and pseudo-3D raycasting.

---

## ✅ Responsibilities & ❌ Anti-Responsibilities
- **Must:** Orchestrate the high-level flow: Update -> Render -> Display.
- **Must:** Synchronize world state between the physics and animation layers.
- **Must:** Optimize the rendering pipeline using the SAH BVH and spatial partitioning.
- **Must:** Manage global engine resources (texture caches, global timers).
- **Must Not:** Directly handle OS-level windowing (delegated to `window/`).
- **Must Not:** Perform raw map parsing (delegated to `helpers/parser/`).

---

## 🔄 Engine Orchestration Pipeline
```mermaid
graph TD
    A[MLX Loop Hook] --> B[Physics Tick]
    B --> C[Animation Update]
    C --> D[Render Scene]
    D --> E[Draw UI / HUD]
    E --> F[MLX Push Buffer]
    
    subgraph Physics
        B1[DDA Traversal]
        B2[Collision Resolution]
    end
    
    subgraph Render
        D1[Raycasting]
        D2[Sprite Sorting]
        D3[Floor/Ceiling]
    end
```

---

## 🧱 Sub-Modules Matrix
| Module | Primary Responsibility | Documentation |
| :--- | :--- | :--- |
| **`physics/`** | Movement, DDA, and Collision resolution. | [README](physics/README.md) |
| **`animation/`** | Sprite rendering and entity state management. | [README](animation/render/README.md) |
| **`optimization/`** | SAH BVH build and spatial queries. | [README](optimization/README.md) |
| **`render/`** | High-level scene assembly and UI drawing. | *Internal* |

---

## 🧠 Global Engine Strategy
The engine follows a strict **Command & Control** pattern:
- **`engine.c`** (or `render_frame`) acts as the conductor, calling into specialized sub-modules in a specific order to ensure that collisions are resolved before animations are calculated, and animations are ticked before the final render.
- **Data Persistence**: Shared state like the **Z-Buffer** is generated during wall-casting and passed to the sprite-rendering module to handle occlusion.

---

## 🛡️ Memory & Resource Philosophy
> [!IMPORTANT]
> **Asset Lifecycle:** Textures and animation clips are shared resources managed via the `tex_cache`. They are loaded once at startup and reused across all entities to minimize memory footprint.

> [!CAUTION]
> **Thread Safety (Ready):** The engine is designed with a "Read-Only" render phase, meaning the world state is locked while the raycaster is walking the BVH, preparing the foundation for future multi-threaded optimizations.

---

## 🗂️ Files Inventory
| File | Role |
| :--- | :--- |
| `render/` | Handles the visual output (Raycasting, Sprites, HUD). |
| `physics/` | Handles the spatial logic (DDA, Collisions). |
| `animation/` | Handles dynamic world entities. |
| `optimization/` | Spatial acceleration structures (SAH BVH). |
