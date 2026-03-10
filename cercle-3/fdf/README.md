# 🌐 **FDF** - *Fil de Fer*

> **A high-performance 3D terrain visualizer**  
> Transforming `.fdf` heightmaps into interactive wireframe and filled landscapes
> with a custom rendering pipeline built in C.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=for-the-badge)
![Architecture](https://img.shields.io/badge/Architecture-Modular-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Stable-success?style=for-the-badge)

---

## 📖 **Overview**

**FDF** is a 42-school graphics project that renders topographic maps as a live,
interactive 3D scene. This implementation goes beyond the minimal wireframe goal
with a full camera system, multiple projection modes, dynamic tessellation,
runtime terrain generation, an information overlay, and a modular rendering
pipeline split across dedicated engine subsystems.

The project takes `.fdf` grid files, converts them into structured map data,
applies camera and projection transforms, culls unnecessary geometry, and then
rasterizes the result into the display buffer with custom line and triangle code.

---

## ✨ **Key Features**

| Feature | Description |
| :--- | :--- |
| **🚀 Real-Time Rendering** | Custom line, grid, and triangle drawing pipeline with depth-aware rasterization. |
| **📐 Dual Projection Modes** | Switch between parallel and perspective views while keeping the scene interactive. |
| **🎨 Dynamic Styling** | Height-based palettes, source-color mode, GUI themes, and runtime visual toggles. |
| **🔍 Full Navigation** | Rotate, zoom, pan, align, and reset the camera in real time. |
| **⚙️ Adaptive Detail** | LOD controls, tessellation levels, and render optimizations for larger terrains. |
| **🖥️ Live GUI Overlay** | On-screen status panels expose rendering state, transforms, and controls. |
| **🌋 Terrain Generation** | Built-in runtime generation plus an external Python generator for custom maps. |

---

## 🎮 **Controls**

Navigate the terrain with keyboard and mouse input.

### **Camera Movement & View**
| Command | Action |
| :--- | :--- |
| `Arrow Keys` | Translate camera on the X/Y plane |
| `Scroll Wheel` | Zoom in or out |
| `Left Click + Drag` | Rotate the view |
| `Right Click + Drag` | Adjust precision rotation |
| `SPACE` | Reset camera position |

### **Rotation & Alignment**
| Command | Action |
| :--- | :--- |
| `X` / `Y` / `Z` | Toggle continuous rotation around an axis |
| `W` + `+/-` | Adjust rotation speed |
| `Q` / `E` / `U` | Align view to side, front, or top |
| `R` | Reset rotation state |

### **Rendering & Tuning**
| Command | Action |
| :--- | :--- |
| `P` | Toggle projection mode |
| `+/-` | Apply combo-based adjustments to active parameters |
| `Page Up` / `Page Down` | Adjust tessellation level |
| `Home` / `End` | Adjust LOD |
| `A` + `+/-` | Adjust field of view / angle |
| `D` + `+/-` | Adjust dampening |
| `F` + `+/-` | Adjust frustum margin |

### **System & Visual Toggles**
| Command | Action |
| :--- | :--- |
| `TAB` | Cycle loaded maps |
| `S` | Cycle GUI theme or style |
| `C` | Toggle color mode |
| `G` | Generate a new runtime map |
| `I` | Toggle information overlay |
| `H` | Toggle help overlay |
| `ESC` | Exit the application |

---

## 🛠️ **Build & Run**

### **Prerequisites**

- `gcc` or `clang`
- `make`
- X11 development libraries such as `libx11-dev` and `libxext-dev`
- MiniLibX sources in `minilibx-linux/`

### **Build**

```bash
git clone https://github.com/Abdoulkadir-ali/42cursus
cd cercle-3/fdf
make
```

### **Run**

```bash
./fdf maps/test_maps/00_simple.fdf
./fdf maps/test_maps/
./fdf maps/generated_maps/
```

If you launch `./fdf` without an argument, the application defaults to the
generated map directory.

---

## 🧠 **Architecture**

The codebase is organized as a modular engine with clear subsystem boundaries.

| Module | Responsibility |
| :--- | :--- |
| `srcs/core` | Bootstrap, runtime setup, and cleanup |
| `srcs/window` | MLX window creation and initial display setup |
| `srcs/events` | Mouse, keyboard, hooks, loop updates, and runtime toggles |
| `srcs/geometry` | Map loading, parsing, styling, generation, and tessellation |
| `srcs/render` | Camera handling, projection stages, culling, and render flow |
| `srcs/graphics` | Frame buffers, rasterization, line drawing, grid traversal, and triangle fill |
| `srcs/gui` | HUD, panels, labels, transforms, and visual themes |
| `srcs/primitives` | Vectors, matrices, and shared math helpers |

### **Pipeline Summary**

1. Load or generate map data.
2. Prepare camera and projection transforms.
3. Cull or simplify geometry when possible.
4. Rasterize wireframe or filled output into buffers.
5. Draw GUI overlays.
6. Present the frame and respond to the next input event.

---

## 🗺️ **Map Format**

FDF reads `.fdf` files as height grids.

- Each line is one row of the map.
- Each space-separated token is one point.
- Integer values represent height on the Z axis.
- Tokens can optionally include a source color in hexadecimal form.

### **Accepted Tokens**

```text
42
-3
10,0xFF0000
0,0x00FFAA
```

### **Example**

```text
0 0 0 0 0
0 10 10 10 0
0 10 20 10 0
0 10 10 10 0
0 0 0 0 0
```

For a fuller description of the map format and usage patterns, see `maps/README.md`.

---

## 🌋 **Map Generation**

FDF supports two complementary ways to create terrain.

### **Runtime Generator**

Inside the application, press `G` to generate a new procedural map from seeded
noise. This is useful for live experimentation and render testing.

### **Python Generator**

The standalone tool in `generator/generate.py` can generate:

- noise-based terrains
- flat test grids
- image-derived heightmaps with preserved source colors

Example commands:

```bash
python3 generator/generate.py alpine --mode noise --width 300 --height 300 --scale 40
python3 generator/generate.py baseline --mode flat --width 50 --height 50
python3 generator/generate.py --mode image --image generator/pictures --width 250 --height 250 --scale 60
```

---

## 📚 **Documentation Map**

The repository now includes module-level READMEs for deeper navigation.

| Path | Description |
| :--- | :--- |
| `srcs/README.md` | Full engine-level architecture overview |
| `includes/README.md` | Public headers and interface layer |
| `maps/README.md` | `.fdf` format, sample maps, and usage |
| `generator/README.md` | External Python terrain generator |
| `libft/README.md` | Custom support library used across the project |

---

## 📜 **License**

This project is open-source and distributed under the [MIT License](LICENSE).

---

<center>
  <sub>Designed & Developed by <b>Antigravity</b> for the 42 Curriculum.</sub>
</center>