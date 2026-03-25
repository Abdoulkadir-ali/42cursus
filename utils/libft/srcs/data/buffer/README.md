# 🧰 Dynamic Buffer Subpackage (`packages/libft/srcs/data/buffer`)

![Domain](https://img.shields.io/badge/Domain-Dynamic_Byte_Buffer-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Minimal-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Small, allocation-friendly dynamic byte buffer used across the codebase for building strings and temporary IO payloads. Provides deterministic growth, nul-terminated access and simple mutation primitives.

---

## ⚙️ Core Mechanic & Algorithms
- `t_buffer` holds a contiguous `char *` storage with `len` and `cap` fields.
- `ft_buffer_reserve` grows capacity geometrically (doubling) to amortize push costs and uses `ft_memcpy` for efficient relocation.
- Append helpers (`append/`) write in-place and maintain a terminal `\0` so buffer contents can be accessed as a C-string without extra copies.

Design favors predictable memory patterns and minimal heap churn for shell-critical hot paths.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> The dynamic buffer is nul-terminated after all append operations to safely interoperate with legacy C string functions. Callers that stream the buffer to file descriptors should handle `write(2)` return values.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_buffer_new` / `ft_buffer_free` | `YES` / `NO` | Caller creates/frees the `t_buffer` structure and backing store |
| Append helpers (`ft_buffer_append*`) | `NO` | Mutate in-place; may trigger internal reallocation via `ft_buffer_reserve` |
| `ft_buffer_to_string` | `YES` | Caller must `free()` returned NUL-terminated copy |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - Passing `NULL` buffers to append helpers is an error; `ft_buffer_append_str(NULL)` returns silently only when the source string is `NULL`.
> - Not suitable for concurrent mutation without external locking; these APIs are not thread-safe.
