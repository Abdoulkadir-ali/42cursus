# 🧾 **Includes** - *Public Interfaces*

> **The contract layer of push_swap**  
> A compact header layer that exposes the structures, constants, and function
> declarations shared by the sorting engine and checker.

![Headers](https://img.shields.io/badge/Layer-Public%20API-1f6feb?style=for-the-badge)
![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Role](https://img.shields.io/badge/Purpose-Interfaces-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Docs-Complete-success?style=for-the-badge)

---

## 📖 **Overview**

The `includes/` directory gathers the public header used across the whole
`push_swap` project. It defines the shared structures, compile-time flags, and
function prototypes that connect parsing, stack operations, sorting logic,
debug helpers, and checker execution through one stable interface.

If `srcs/` is the engine room, `includes/` is the wiring diagram.

---

## 🗂️ **Header Map**

| Header | Responsibility |
| :--- | :--- |
| `push_swap.h` | Main project header exposing stacks, metadata, operations, parsing, algorithm, and checker interfaces |

---

## ⚙️ **How It Works**

Each implementation file under `srcs/push_swap/` depends on declarations from
`push_swap.h`. That header centralizes the project contract so modules can stay
focused on implementation while still sharing the same types and function
signatures.

It provides a common interface for:

- runtime flags such as `DEBUG`
- core structures like `t_nodes`, `t_stacks`, and algorithm context structs
- stack manipulation operations
- parsing and validation helpers
- cost, target, and sorting routines
- checker instruction execution

The result is a simpler codebase where declarations stay consistent and module
boundaries remain easy to follow.

---

## 🔗 **Dependency Role**

The header in this folder forms the bridge between the major runtime areas:

```text
parsing <-> operations <-> algorithm
algorithm <-> target / cost / moves
checker <-> parsing / operations
debug helpers <-> stacks / algorithm
```

`push_swap.h` acts as the shared vocabulary for the entire project.

---

## 🛠️ **Developer Notes**

- Keep implementation details in `srcs/`; reserve `includes/` for shared public contracts.
- Changes here affect the full project because most modules include this header directly.
- Struct and prototype changes should stay synchronized with the implementation files.
- Header clarity matters because this file defines the public shape of the project.

---

## 📚 **Related Files**

- Main project overview: `../README.md`
- Engine implementation: `../srcs/push_swap/`
- Utility library header: `../packages/libft/includes/libft.h`

---

<center>
	<sub>`includes/` defines the shared interface used by every push_swap subsystem.</sub>
</center>