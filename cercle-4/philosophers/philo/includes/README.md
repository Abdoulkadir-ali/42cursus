# 🧾 **Includes** - *Public Interfaces*

> **The contract layer of philosophers**  
> A compact header layer that exposes the structures, constants, and function declarations shared by the simulation engine and thread routines.

![Headers](https://img.shields.io/badge/Layer-Public%20API-1f6feb?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Role](https://img.shields.io/badge/Purpose-Interfaces-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Docs-Complete-success?style=for-the-badge)

---

## 📖 **Overview**

The `includes/` directory gathers the public header used across the whole philosophers project. It defines the shared structures, compile-time flags, and function prototypes that connect argument parsing, simulation rules, thread routines, and utility helpers through one stable interface.

If `srcs/` is the engine room, `includes/` is the wiring diagram.

---

## 🗂️ **Header Map**

| Header      | Responsibility |
| :---        | :--- |
| `philo.h`   | Main project header exposing rules, philosopher structs, mutexes, thread routines, and utility interfaces |

---

## ⚙️ **How It Works**

Each implementation file under `srcs/` depends on declarations from `philo.h`. That header centralizes the project contract so modules can stay focused on implementation while still sharing the same types and function signatures.

It provides a common interface for:
- simulation rules and configuration
- philosopher and thread data
- mutexes and synchronization primitives
- argument parsing and validation helpers
- thread routines (eat, sleep, think, death)
- utility functions for printing and timing

The result is a simpler codebase where declarations stay consistent and module boundaries remain easy to follow.

---

## 🔗 **Dependency Role**

The header in this folder forms the bridge between the major runtime areas:

```text
core <-> routine <-> lib
routine <-> thread data / mutexes
lib <-> printing / timing / conversion
```

`philo.h` acts as the shared vocabulary for the entire project.

---

## 🛠️ **Developer Notes**

- Keep implementation details in `srcs/`; reserve `includes/` for shared public contracts.
- Changes here affect the full project because most modules include this header directly.
- Struct and prototype changes should stay synchronized with the implementation files.
- Header clarity matters because this file defines the public shape of the project.

---

## 📚 **Related Files**

- Main project overview: `../README.md`
- Source pipeline: `../srcs/README.md`
