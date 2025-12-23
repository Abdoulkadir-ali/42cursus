# 🌐 **FDF** - *Fil de Fer*

> **A High-Performance 3D Wireframe Visualizer**  
> Rendering topographic landscapes with unparalleled speed and aesthetic precision.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Stable-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**FDF** (Fil de Fer) transforms raw topographic data into stunning, interactive 3D wireframe landscapes. Built with a custom graphics engine on top of MiniLibX, it features advanced rendering techniques like **Bresenham's Line Algorithm**, **Sutherland-Hodgman Clipping**, and a highly optimized **MVP (Model-View-Projection) Pipeline**.

Explore terrains with smooth real-time rotations, dual projection modes, dynamic tessellation, and a suite of vibrant color themes.

---

## ✨ **Key Features**

| Feature | Description |
| :--- | :--- |
| **🚀 High-Performance Rendering** | SIMD-optimized vector math and multi-threaded processing for fluid 60 FPS visuals. |
| **📐 Dual Projection Modes** | Switch seamlessly between **Parallel (Isometric)** and **Conic (Perspective)** views. |
| **🎨 Dynamic Aesthetics** | Choose from rich color themes: *Matrix*, *Cyberpunk*, *Tron Blue*, *Neon Grid*, and more. |
| **🔍 Interactive Exploration** | Full 3D camera control: rotate, zoom, pan, and fly through your terrain. |
| **⚙️ Advanced Tesselation** | Adaptive mesh subdivision adds detail where it matters, reducing artifacts. |
| **🖥️ GUI Overlay** | Real-time on-screen status display for active parameters and controls. |

---

## 🎮 **Controls**

Navigate your world with precision using keyboard and mouse inputs.

### **Camera Movement & View**
| Command | Action |
| :--- | :--- |
| `Arrow Keys` | **Translate** Camera (Pan X/Y) |
| `Scroll Wheel` | **Zoom** In / Out |
| `Left Click + Drag` | **Rotate** View Orbit |
| `Right Click + Drag` | **Precision Rotate** |
| `SPACE` | **Reset** Camera Position |

### **Rotation Controls**
| Command | Action |
| :--- | :--- |
| `X` / `Y` / `Z` | Toggle Continuous Axis Rotation |
| `W` + `+/-` | Adjust Rotation Speed |
| `Q` / `E` / `U` | Align View to **Side**, **Front**, or **Top** |
| `R` | Reset Rotation State |

### **Rendering Parameters**
| Command | Action |
| :--- | :--- |
| `P` | Toggle **Projection Mode** (Parallel / Perspective) |
| `+/-` | Sensitivity / Zoom adjustments |
| `Page Up` / `Down` | Adjust **Tessellation Level** |
| `Home` / `End` | Adjust **LOD** (Level of Detail) |
| `A` + `+/-` | Adjust **FOV / Angle** |
| `D` + `+/-` | Adjust **Dampening** |
| `F` + `+/-` | Adjust **Frustum Margin** |

### **System & Aesthetics**
| Command | Action |
| :--- | :--- |
| `TAB` | **Cycle Maps** (Next/Prev in directory) |
| `S` | **Cycle GUI Themes** |
| `C` | **Cycle Color Palettes** |
| `I` | Toggle Info Overlay |
| `H` | Toggle Help Menu |
| `ESC` | **Exit Application** |

---

## 🛠️ **Installation**

Get **FDF** running on your Linux machine in seconds.

### **Prerequisites**
- **GCC / Clang** compiler
- **Make**
- **X11** development libraries (`libx11-dev`, `libxext-dev`)

### **Build Instructions**

```bash
# 1. Clone the repository
git clone https://github.com/Abdoulkadir-ali/42cursus.git fdf
cd fdf

# 2. Compile the project
make

# 3. Run FDF
./fdf maps/42.fdf
```

> 💡 **Tip:** If you run `./fdf` without arguments, it will automatically load all maps from the `maps/` directory for quick cycling!

---

## 🧠 **Technical Architecture**

The project is structured for modularity and performance.

### **Core Components**
- **`srcs/core`**: Main loop and cleanup.
- **`srcs/graphics`**: The heart of the renderer (Bresenham, Raycasting, Pixel/Line drawing).
- **`srcs/render`**: Camera logic, Matrix transformations (Translation, Rotation, Scaling).
- **`srcs/geometry`**: Vector math library, tessellation logic, and map parsing.
- **`srcs/events`**: Robust input handling system.
- **`srcs/gui`**: Overlay and HUD rendering.

### **Optimization Techniques**
- **SIMD (AVX/SSE)**: Vectorized math operations for heavy matrix multiplications and vertex transformations.
- **View Frustum Culling**: Discards geometry outside the camera's view before the expensive rasterization stage.
- **Backface Culling**: Optimized line drawing logic to skip hidden surfaces.
- **Z-Buffering**: Accurate depth management for artifact-free 3D representation.

---

## 🗺️ **Format Specification**

FDF reads `.fdf` files, a simple text-based format for 3D grids.

- **Rows**: Lines in the file correspond to grid Y-coordinates.
- **Columns**: Space-separated values correspond to grid X-coordinates.
- **Values**: Integers representing the **Z-height** at that point.
- **Color (Optional)**: Hex code appended to height, e.g., `10,0xFF0000`.

**Example:**
```text
0  0  0  0  0
0 10 10 10  0
0 10 20 10  0
0 10 10 10  0
0  0  0  0  0
```

---

## 📜 **License**

This project is open-source and available under the [MIT License](LICENSE).

---

<center>
  <sub>Designed & Developed by <b>Antigravity</b> for the 42 Curriculum.</sub>
</center>