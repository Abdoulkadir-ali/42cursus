# 🔦 **miniRT** - *Drawing with rays*

> **A powerful and optimized Ray Tracer implementation in C.**  
> Exploring the physics of light, complex geometry, and advanced acceleration structures.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**miniRT** is a 42 school project focused on building a fully functional Ray Tracing engine from scratch. It simulates the behavior of light hitting objects to create realistic 3D images. The project covers fundamental computer graphics concepts like intersection math, lighting models (Phong/Blinn-Phong), material properties, and performance optimization through hierarchical spatial structures.

---

## ✨ **Features**

### 📐 **Geometry & Primitives**
- **Core Shapes**: Precise mathematical intersection for Spheres, Planes, Cylinders, and Cones.
- **Complex Meshes**: Render high-poly models with thousands of triangles.
- **Transformations**: Full support for world-space translation, rotation, and scaling.

### 🚀 **Performance Optimization**
- **Optimized BVH**: Bounding Volume Hierarchy using **Binned Surface Area Heuristic (SAH)** for ultra-fast ray-mesh intersection.
- **AABB Slab Test**: High-performance Axis-Aligned Bounding Box intersection tests.
- **Multi-threading**: Leverages `pthreads` to distribute rendering tasks across CPU cores.

### 🎨 **Materials & Textures**
- **XPM Support**: Map textures and bump maps onto objects using MinilibX.
- **Advanced Materials**: Support for metallic properties, roughness, emission, and refraction.
- **Lighting**: Point lights, Spot lights, and configurable Ambient lighting.

### 📂 **Universal Parsing**
- support for multiple model formats:
  - **.obj**: Standard Wavefront models with MTL support.
  - **.fbx**: Both Binary and ASCII formats.
  - **.glb**: Binary glTF for modern asset support.
  - **.fdf**: Custom heightmap format.
  - **.rt**: Custom scene definition language.

---

## 🏗️ **Project Layout**

- `srcs/core/` — Program entry, signal handling, and interactive loops.
- `srcs/rays/` — Raytracing kernels, BVH traversal, and shading logic.
- `srcs/objects/` — Primitive definitions and advanced model parsers.
- `srcs/parser/` — Scene and model parsing infrastructure (RT, JSON, etc.).
- `srcs/gui/` — MinilibX wrappers, window management, and frame buffering.
- `srcs/utils/` — Math library (vectors, matrices), dynarrays, and path helpers.
- `includes/` — Project headers and public APIs.
- `packages/` — Bundled dependencies like `libft` and `minilibx-linux`.

---

## 🛠️ **Build Instructions**

### Prerequisites
- A POSIX toolchain (`cc`, `make`).
- `X11` development libraries (for MinilibX).
- `zlib` (for FBX decompression).

### Build from source
```bash
make
```

### Common Targets
- `make` — Builds the `miniRT` executable.
- `make clean` — Removes object files.
- `make fclean` — Removes objects and the binary.
- `make re` — Full rebuild.

---

## 🚀 **Running miniRT**

Start the renderer by passing a scene file:

```bash
./miniRT maps/rt/obj_showcase.rt
```

### Interactive Controls
- `WASD / QE` — Move camera.
- `Arrows` — Rotate camera.
- `N` — Cycle through available maps in the `maps/` directory.
- `ESC` — Exit program.

---

## 🧪 **Testing & Debugging**

- **Debug Print**: The project includes a comprehensive debug printing system for vectors, transforms, and object states.
- **Leaks**: Use Valgrind to ensure memory safety during complex model parsing:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./miniRT maps/rt/obj_showcase.rt
```

---

## 📜 **License**

This project is licensed under the MIT License. See the libft and minilibx-linux directories for their respective licenses.

---

*Found a bug? Feel free to open an issue or submit a pull request!*
