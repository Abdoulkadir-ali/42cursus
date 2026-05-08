# 🔬 Linked-List Generator Subpackage (`packages/libft/srcs/lst`)

![Domain](https://img.shields.io/badge/Domain-Structural_Pointers-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Provides massive scale heap generation of dynamic nodes (`t_list`) heavily utilized as AST building blocks or environment-tracking buffers across the global Minishell application.

---

## ⚙️ Core Mechanic & Algorithms
**The Singly-Linked Schema:**
1. A node `t_list` possesses exactly two native variables: `void *content` and `struct s_list *next`.
2. Operations natively jump via loop pointers: `while (node->next) { node = node->next }`. No pointer arithmetic is required or allowed here.
3. The `ft_lstmap` engine allows functional mapping identically to Python's `map()`. It dynamically allocates a brand new secondary list strictly applying an injected `f(void *)` function wrapper against every physical node.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Void Contexts:** The `content` tracker natively implements generic `void *` bindings over explicit types. This ensures `libft` can dynamically hold integers, 2D Shell Tokens, or entire structurally-typed Bash Subshells generically without altering list implementations.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_lstnew()` | `YES` via `malloc` | Caller MUST call `free()` on the generated node. |
| `ft_lstclear()` | `NO` (`free()` bounds) | Explicitly targets and dismantles *all* memory allocations sequentially down the list tracker. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Orphaned Content Arrays:** If `ft_lstdelone` is called natively but the provided `del()` function signature is set improperly to `NULL`, the `void *content` is permanently orphaned in the Heap, creating invisible structural memory leaks throughout the execution process.
