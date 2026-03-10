# 🧾 **Includes** - *Public Interfaces*

> **The contract layer of FDF**  
> A compact set of headers that expose the structures, constants, and function
> declarations used across the engine.

![Headers](https://img.shields.io/badge/Layer-Public%20API-1f6feb?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Role](https://img.shields.io/badge/Purpose-Interfaces-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Docs-Complete-success?style=for-the-badge)

---

## 📖 **Overview**

The `includes/` directory gathers the public headers that tie the whole FDF
engine together. These files define shared structures, constants, enums, and
function prototypes so each runtime module can stay focused on implementation
while depending on a stable interface layer.

If `srcs/` is the engine room, `includes/` is the wiring diagram.

---

## 🗂️ **Header Map**

| Header | Responsibility |
| :--- | :--- |
| `fdf.h` | Main project umbrella header tying major modules together |
| `define.h` | Global constants, macros, and shared compile-time definitions |
| `core.h` | Startup, initialization, and cleanup contracts |
| `window.h` | Window creation and display bootstrap interfaces |
| `events.h` | Input state, hooks, and event-dispatch contracts |
| `geometry.h` | Maps, colors, tessellation, and terrain-generation interfaces |
| `graphics.h` | Draw state, buffers, raster helpers, and low-level rendering contracts |
| `render.h` | Camera management, projection stages, culling, and render pipeline interfaces |
| `gui.h` | Overlay layout, panels, themes, and print helpers |
| `primitives.h` | Vector, matrix, and clamp utilities used across the engine |
| `generator.h` | Procedural terrain-generation interfaces and noise helpers |

---

## ⚙️ **How It Works**

Each implementation directory in `srcs/` exposes its public surface through one
or more headers in `includes/`. This keeps module boundaries clear:

- runtime code includes only the interfaces it needs
- shared structs stay consistent across folders
- large subsystems such as rendering, events, and geometry can evolve without
  duplicating declarations

The result is a modular project layout where source files remain relatively
small and responsibilities stay easy to trace.

---

## 🔗 **Dependency Role**

The headers in this folder form the bridge between these major areas:

```text
core <-> window <-> graphics
events <-> render <-> graphics
geometry <-> render
gui <-> graphics
primitives -> geometry / render / graphics / gui
```

Most modules depend on `primitives.h` directly or indirectly, while `fdf.h`
acts as the higher-level aggregation point for the main program.

---

## 🛠️ **Developer Notes**

- Keep implementation details in `srcs/`; reserve `includes/` for shared public contracts.
- Changes here affect multiple modules, so header edits have the widest impact on builds.
- The header set mirrors the runtime architecture closely, which makes navigation straightforward.
- Norminette compliance matters here because prototype formatting errors propagate quickly.

---

## 📚 **Related Files**

- Engine implementation: `../srcs/README.md`
- Main project overview: `../README.md`
- Utility library header: `../libft/includes/libft.h`

---

<center>
  <sub>`includes/` defines the vocabulary shared by every subsystem in FDF.</sub>
</center>