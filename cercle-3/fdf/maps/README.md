# 🗺️ **Maps** - *Terrain Inputs*

> **The data layer of FDF**  
> A collection of `.fdf` terrain files used to test, demonstrate, and stress the
> renderer, plus the format rules needed to create new maps correctly.

![Data](https://img.shields.io/badge/Content-Terrain%20Maps-1f6feb?style=for-the-badge)
![Format](https://img.shields.io/badge/Format-.fdf-orange?style=for-the-badge)
![Usage](https://img.shields.io/badge/Role-Input%20Data-success?style=for-the-badge)
![Tests](https://img.shields.io/badge/Test%20Set-Versioned-brightgreen?style=for-the-badge)

---

## 📖 **Overview**

The `maps/` directory contains the terrain files consumed by FDF. These files
describe a 2D grid of heights that the engine transforms into a 3D wireframe or
filled terrain view. They are used both for visual demonstrations and for
testing edge cases such as tiny maps, flat areas, negative values, and more
complex elevation patterns.

---

## 🗂️ **Directory Structure**

| Directory | Purpose |
| :--- | :--- |
| `test_maps/` | Versioned sample maps used for development, debugging, and evaluation |
| `generated_maps/` | Larger or generated terrain files used for runtime experiments and showcases |

`test_maps/` is intentionally kept trackable in git so small deterministic inputs
remain available for debugging and regression checks.

---

## 📐 **FDF File Format**

Each `.fdf` file represents a rectangular grid.

### **Rules**

- Each line in the file is one row of the terrain.
- Each space-separated token is one point in that row.
- The numeric value is the point's **Z height**.
- Rows define the **Y axis**, and token position defines the **X axis**.
- Tokens may optionally include a color in hexadecimal form.

### **Basic Token Forms**

```text
42
-3
10,0xFF0000
0,0x00FFAA
```

### **Examples**

Simple flat map:

```text
0 0 0 0 0
0 0 0 0 0
0 0 1 0 0
0 0 0 0 0
0 0 0 0 0
```

Colored map:

```text
0,0xFFFFFF 1,0x00FF00 2,0xFF0000
1,0xFFFFFF 2,0x00FF00 3,0xFF0000
2,0xFFFFFF 3,0x00FF00 4,0xFF0000
```

---

## ▶️ **How To Use Maps**

### **Load a Single Map**

```bash
./fdf maps/test_maps/00_simple.fdf
```

### **Load a Directory of Maps**

```bash
./fdf maps/test_maps/
```

When a directory is loaded, FDF builds an internal list of `.fdf` files and lets
you cycle through them during runtime.

---

## 🧪 **Practical Usage**

Use `test_maps/` when you want deterministic fixtures for:

- parser validation
- camera behavior checks
- rendering regressions
- tessellation and LOD experiments
- color-mode and style testing

Use `generated_maps/` when you want broader visual variety or larger terrain
inputs for stress and performance checks.

---

## 🛠️ **Tips For Writing New Maps**

- Keep rows consistent in length when possible for predictable grids.
- Use small maps first when debugging parsing or rendering issues.
- Add explicit colors only when testing source-color behavior.
- Mix positive and negative heights to test gradient and projection behavior.
- Store reusable debug fixtures in `test_maps/`.

---

## 🔍 **How FDF Reads These Files**

At runtime, the geometry module:

1. enumerates `.fdf` files from the chosen directory
2. measures width and height from non-empty rows
3. allocates map buffers
4. parses heights and optional colors
5. computes `min_max_z`, `z_divisor`, and styled display colors

This means the files in `maps/` are not just assets; they are the starting point
for the entire terrain pipeline.

---

## 📚 **Related Files**

- Geometry module docs: `../srcs/geometry/README.md`
- Source-tree overview: `../srcs/README.md`
- Main project overview: `../README.md`

---

<center>
  <sub>`maps/` provides the terrain data that FDF turns into interactive 3D landscapes.</sub>
</center>