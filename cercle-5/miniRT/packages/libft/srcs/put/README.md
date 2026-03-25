# 📢 Output Helpers Subpackage (`packages/libft/srcs/put`)

![Domain](https://img.shields.io/badge/Domain-IO_Primitives-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Portable-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Lightweight output primitives that wrap file-descriptor based writes (`fd/`) and formatted printing helpers (`printf/`). Designed for predictable behavior in shells and daemons.

---

## ⚙️ Core Mechanic & Algorithms
- `fd/` utilities provide minimal wrappers around `write(2)` with null checks and return-value forwarding.
- `printf/` helpers implement a compact, `libft`-scoped formatter used across the project; they minimize buffering and avoid locale-dependent behavior.

Implementations favor small stack buffers and explicit `write` calls to ensure output ordering in pipelined contexts.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> These modules use plain `int` file descriptors and avoid stdio buffering to maintain exact sequencing with shell pipelines and signal handlers.

---

## 💾 Memory Contracts
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `printf/` internals | Rarely (for formatting) | Caller frees returned strings if any |
| `fd/` helpers | `NO` | Stateless wrappers around `write(2)` |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - `write` may return partial writes; callers relying on atomicity should handle return values accordingly.
> - `printf`-style helpers intentionally avoid locale-dependent formatting and floating-point support.
