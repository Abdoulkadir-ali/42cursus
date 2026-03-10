# 🏔️ **Generator** - *Terrain Creation Tools*

> **Create `.fdf` maps outside the main runtime**  
> A standalone utility layer for producing procedural terrains, flat fixtures,
> and image-based heightmaps ready to load in FDF.

![Tooling](https://img.shields.io/badge/Tooling-Map%20Generator-1f6feb?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-Python-3776AB?style=for-the-badge&logo=python&logoColor=white)
![Output](https://img.shields.io/badge/Format-.fdf-orange?style=for-the-badge)
![Modes](https://img.shields.io/badge/Modes-Noise%20%7C%20Image%20%7C%20Flat-success?style=for-the-badge)

---

## 📖 **Overview**

The `generator/` folder contains the external map-generation tool used to create
new `.fdf` terrain files for FDF. It complements the runtime generator inside
the application by offering a script-driven workflow for producing large maps,
image-derived reliefs, and deterministic test inputs before launching the program.

The generated files are written in the same `.fdf` format consumed by the
geometry loader, which makes this folder a direct content pipeline into `maps/`.

By default, generated files are written to `./maps/generated_maps`.

---

## 🗂️ **Directory Structure**

| Entry | Purpose |
| :--- | :--- |
| `generate.py` | Main CLI utility for generating `.fdf` maps |
| `pictures/` | Reference images that can be converted into terrain maps |

---

## ✨ **Supported Modes**

| Mode | Description |
| :--- | :--- |
| `noise` | Builds a terrain from layered Perlin-style noise |
| `image` | Converts image brightness into height values and preserves source colors |
| `flat` | Produces a zero-height grid useful for parser and rendering tests |

---

## ⚙️ **How It Works**

### **Noise Mode**
- builds a shuffled permutation table and directional gradients
- samples layered noise for each grid point
- scales the result into integer height values
- saves the final grid as a `.fdf` file

### **Image Mode**
- loads an input image with Pillow
- preserves aspect ratio while resizing to fit the requested dimensions
- converts pixel luminance into height values
- stores original pixel colors alongside heights in `.fdf` tokens
- processes folders in sorted filename order for predictable output runs

### **Flat Mode**
- creates a uniform zero-valued map
- useful for baseline tests and predictable visual checks

---

## ▶️ **Usage**

### **Generate a Noise Map**

```bash
python3 generator/generate.py alpine --mode noise --width 300 --height 300 --scale 40
```

### **Generate a Flat Map**

```bash
python3 generator/generate.py baseline --mode flat --width 50 --height 50
```

### **Convert One Image**

```bash
python3 generator/generate.py --mode image --image generator/pictures/sample.png --width 250 --height 250 --scale 60
```

### **Convert All Images In A Folder**

```bash
python3 generator/generate.py --mode image --image generator/pictures --width 300 --height 300 --scale 80
```

If no output name is provided for non-image modes, the script generates a unique
filename automatically.

For image mode, `--image` is mandatory. The script also rejects zero or negative
dimensions before generation starts.

---

## 🧾 **CLI Arguments**

| Argument | Meaning |
| :--- | :--- |
| `name` | Optional output filename |
| `--mode`, `-m` | Generation mode: `noise`, `image`, or `flat` |
| `--width`, `-w` | Output map width |
| `--height`, `-H` | Output map height |
| `--scale`, `-z` | Height multiplier used as z scale |
| `--image`, `-i` | Input image path or image directory for image mode |
| `--folder`, `-f` | Output directory, defaulting to `./maps/generated_maps` |

---

## 🧠 **Output Format**

The script writes standard `.fdf` files:

- noise and flat modes output plain integer heights
- image mode outputs `height,0xRRGGBB` tokens so the runtime can reuse source colors

This means generated maps can be opened immediately with the main binary:

```bash
./fdf maps/generated_maps/
```

---

## 🛠️ **Dependencies**

- Python 3
- `Pillow` for `image` mode

Install Pillow if needed:

```bash
pip install Pillow
```

If Pillow is unavailable, image mode exits with a clear error message while the
other modes remain usable.

---

## 🔍 **Developer Notes**

- Noise generation uses a thread pool to compute rows concurrently.
- Image mode preserves aspect ratio before conversion.
- Folder-based image conversion is processed in sorted order.
- Output defaults to `maps/generated_maps/`, which keeps generated content
  separate from deterministic fixtures in `maps/test_maps/`.
- This tool is ideal for creating large benchmark maps without editing `.fdf`
  files by hand.

---

## 📚 **Related Files**

- Terrain format documentation: `../maps/README.md`
- Runtime geometry loader: `../srcs/geometry/README.md`
- Main project overview: `../README.md`

---

<center>
  <sub>`generator/` turns ideas, noise fields, and images into terrain that FDF can render immediately.</sub>
</center>