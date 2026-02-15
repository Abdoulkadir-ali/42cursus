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
- **Complex Meshes**: Render high-poly models with tens of thousands of triangles (tested with 10K+ face models at 30+ FPS).
- **Transformations**: Full support for world-space translation, rotation, and scaling with automatic BVH rebuild.

### 🚀 **Performance Optimization**
- **Two-Level BVH**: Scene-level pointer-based BVH + per-mesh flat-array BVH using **Binned Surface Area Heuristic (SAH)** with 16 bins.
- **Stackless Near-Child Traversal**: Optimized BVH traversal that jumps directly to the nearer child and only pushes the far child onto the stack.
- **NaN-Safe AABB Slab Test**: Custom `ft_dmin`/`ft_dmax` and `safe_rcp` to handle edge cases under `-ffast-math` compilation.
- **Thread-Local Profiler Counters**: Per-thread counters flushed at end of frame to avoid atomic contention during rendering.
- **Multi-threading**: Tile-based rendering with `pthreads` distributing 32×32 pixel tiles across 12 CPU cores.
- **Precomputed Triangle Cache**: Edge vectors precomputed once for Möller-Trumbore intersection, avoiding redundant math per ray.

### 🎨 **Materials & Textures**
- **Multi-Format Textures**: Load textures from XPM (via MinilibX), JPG, PNG, and BMP (via stb_image).
- **MTL Material Support**: Full Wavefront MTL parsing — `Kd` (diffuse), `Ks` (specular), `Ns` (shininess), `d` (opacity), and `map_Kd` (texture maps).
- **Bump Mapping**: Normal perturbation via tangent-space bump maps with automatic tangent/bitangent computation for all object types including meshes.
- **Advanced Materials**: Support for metallic properties, roughness, emission, refraction index, transparency, and reflectivity.
- **Lighting**: Point lights, Spot lights, and configurable Ambient lighting with Blinn-Phong shading and shadow rays.

### 📂 **Universal Parsing**
- Support for multiple model formats:
  - **.obj**: Standard Wavefront models with MTL material and texture support.
  - **.fbx**: Both Binary and ASCII formats with animation/skinning.
  - **.glb**: Binary glTF for modern asset support.
  - **.fdf**: Custom heightmap format with auto-triangulation.
  - **.rt**: Custom scene definition language.

### 🔍 **Built-in Profiler**
- Real-time per-frame statistics: frame time, FPS, mesh calls, AABB tests, triangle tests, and occlusion queries.
- Compile with `-DPROFILE_MESH` to enable (enabled by default).

---

## 🏗️ **Project Layout**

- `srcs/core/` — Program entry and main loop.
- `srcs/rays/` — Raytracing kernels, BVH construction/traversal, intersection tests, and shading pipeline.
- `srcs/objects/` — Primitive definitions, mesh BVH, and model parsers (OBJ, FBX, GLB, FDF).
- `srcs/parser/` — Scene and model parsing infrastructure (RT, JSON, double parsing).
- `srcs/surface/` — Material system, texture loading (XPM + stb_image), and texture sampling.
- `srcs/gui/` — MinilibX window management, camera controls, tile-based multi-threaded rendering.
- `srcs/maths/` — Vector/matrix math library (vec2, vec3, mat4, quadratics).
- `srcs/utils/` — Dynamic arrays, path utilities.
- `srcs/debug/` — Profiler, debug printers for objects/scene/BVH.
- `includes/` — Project headers and public APIs.
- `packages/` — Bundled dependencies: `libft`, `minilibx-linux`, `stb_image.h`.

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
- `make` — Builds the `miniRT` executable (with `-O3 -ffast-math -flto -pthread`).
- `make clean` — Removes object files.
- `make fclean` — Removes objects and the binary.
- `make re` — Full rebuild.

---

## 🚀 **Running miniRT**

Start the renderer by passing a scene file:

```bash
./miniRT maps/rt/obj_showcase5.rt
```

### Example Scenes
- `maps/rt/test.rt` — Basic primitives test.
- `maps/rt/obj_showcase5.rt` — Garen OBJ model with texture.
- `maps/rt/fdf_showcase.rt` — FDF heightmap rendering.
- `maps/rt/fbx_showcase.rt` — FBX model showcase.
- `maps/rt/megacity.rt` — Stress test with heavy geometry.

### Interactive Controls
- `WASD / QE` — Move camera.
- `Arrows` — Rotate camera.
- `+/-` — Adjust movement speed.
- `Scroll` — Zoom (FOV adjustment).
- `N` — Cycle through available maps in the `maps/` directory.
- `ESC` — Exit program.

---

## 🧪 **Testing & Debugging**

- **Profiler Output**: Real-time frame stats printed to terminal when compiled with `-DPROFILE_MESH`:
```
PROF[100]: 28.8ms (34.7 FPS) mesh=230400 aabb=9434077 tri=5490739 occ=185501
```
- **Debug Print**: Comprehensive debug printing system for vectors, transforms, BVH structure, and object states.
- **Leaks**: Use Valgrind to ensure memory safety:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./miniRT maps/rt/test.rt
```

---

## 📜 **License**

This project is licensed under the MIT License. See the libft and minilibx-linux directories for their respective licenses.

---

*Found a bug? Feel free to open an issue or submit a pull request!*
