# 🚪 Map Entity Primitives (`srcs/primitives/map/door`)

![Subsystem](https://img.shields.io/badge/Subsystem-World_Entities-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Detailed-success?style=for-the-badge)

---

## 🚧 Subsystem Boundary
> [!NOTE]
> **Trigger:** Initialized when the map parser encounters a door ('D') or portal marker in the grid.
> 
> **Output:** Allocates and manages the data structures for dynamic grid cells.

---

## ✅ Responsibilities & ❌ Anti-Responsibilities
- **Must:** Define the `t_door` structure and its state (Open/Closed).
- **Must:** Store spatial coordinates for portals and their linked destinations.
- **Must:** Provide the memory backbone for interactive world geometry.
- **Must Not:** Handle the animation of the door (delegated to `gameplay/entities/door/`).
- **Must Not:** Handle the rendering of the door (delegated to `engine/render/`).

---

## 🧬 Entity Matrix
| Entity Type | Data Structure | Role |
| :--- | :--- | :--- |
| **Door** | `t_door` | Manages blocking vs non-blocking states. |
| **Portal** | `t_portal` | Links two disparate coordinates for teleportation. |

---

## 💾 Memory Contracts
> [!IMPORTANT]
> **Grid Sync:** Doors are stored in a parallel list but are linked to the 2D grid via coordinates. During cleanup, the `free_world()` function must iterate through these lists to ensure no memory leaks.

---

## 🗂️ Files Inventory
| File | Primary Function | Role |
| :--- | :--- | :--- |
| `door.c` | `door_init()` | Allocator for door state structures. |
| `portal.c` | `portal_link()` | Logic for connecting two portal entities. |
