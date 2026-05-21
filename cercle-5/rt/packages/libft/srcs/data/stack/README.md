# 🗂 Stack Subpackage (`packages/libft/srcs/data/stack`)

![Domain](https://img.shields.io/badge/Domain-LIFO_Container-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Minimal-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Lightweight LIFO stack of `void *` pointers for transient parsing and AST-building phases. Designed to be minimal, predictable and easy to embed in higher-level parsers.

---

## ⚙️ Core Mechanic & Algorithms
- The stack uses a contiguous pointer array and geometric growth (doubling) to amortize push costs.
- `ft_stack_reserve` ensures capacity and moves existing pointers with `ft_memcpy` when necessary.
- `ft_stack_push`/`ft_stack_pop` provide the canonical LIFO semantics while keeping operations O(1) amortized.

All functions are small, single-responsibility implementations to simplify reasoning and testing.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> The stack stores raw pointers and does not perform ownership semantics by default; callers must provide a deleter to `ft_stack_free` when items require cleanup.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_stack_new` | `YES` | Caller must `ft_stack_free()` the stack; provide a deleter to free stored items if required |
| `ft_stack_push` / `ft_stack_pop` / `ft_stack_peek` | `NO` | Mutate the stack in-place; returned pointers remain owned by the caller/stack |
| `ft_stack_reserve` | `YES` (internal) | Internal reallocation; caller unaffected besides capacity growth |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - `ft_stack_pop` and `ft_stack_peek` return `NULL` when the stack is empty — callers must check.
> - Multithreaded usage requires external synchronization; the stack is not thread-safe.

