# 🗃️ Data Subpackages (`packages/libft/srcs/data`)

![Domain](https://img.shields.io/badge/Domain-Inmemory_Primitives-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Minimal-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Shared in-memory primitives used across `libft`: dynamic buffers, string helpers, linked lists and lightweight containers (stacks). These modules provide small, well-contained building blocks for parsing, formatting and transient data manipulation.

---

## ⚙️ Core Mechanic & Algorithms
- Each subpackage targets a narrow responsibility (e.g., buffers, lists, stacks, strings) and exposes a tiny, testable API.
- Growth and allocation strategies are conservative: geometric growth for resizable arrays and minimal pointer-chasing for lists.
- Public APIs are implemented as single-responsibility functions to ease Norminette compliance and review.

Typical subpackages:
- `buffer/` — dynamic byte buffers and append helpers
- `buffer/append/` — one-public-function files for append operations
- `lst/` — linked list utilities
- `stack/` — small LIFO container (see stack/README)
- `str/` — string helpers and safe utilities

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> Modules avoid locale-sensitive or non-deterministic behavior. APIs use plain C types and file-descriptor level semantics where applicable to maintain deterministic behavior inside shells and parsers.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| Subpackage constructors (e.g., `ft_buffer_new`, `ft_stack_new`) | `YES` | Caller must call matching free functions (`ft_buffer_free`, `ft_stack_free`) |
| Small helpers (append/pop/peek) | `NO` | Mutate provided structures in-place |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - These primitives are not thread-safe by design; provide external synchronization for concurrent access.
> - Many helpers return `NULL` or sentinel values on error — callers must check and handle these cases.
