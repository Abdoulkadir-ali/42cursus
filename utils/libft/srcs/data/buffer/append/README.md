# 🧱 Buffer Append Subpackage (`packages/libft/srcs/data/buffer/append`)

![Domain](https://img.shields.io/badge/Domain-Dynamic_Buffer_Append-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Minimal-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Small helpers for appending raw bytes, C-strings and single characters into the project `t_buffer` dynamic buffer. These are thin, well-bounded wrappers that keep the buffer nul-terminated and sized correctly for downstream consumers.

---

## ⚙️ Core Mechanic & Algorithms
**Append Path:**
1. Validate inputs (null checks).
2. Ensure capacity via `ft_buffer_reserve` which grows the underlying storage geometrically.
3. Copy bytes with `ft_memcpy` (or assign a single character) and update `len`.
4. Maintain a final `\0` terminator so the buffer can be treated as a C-string when needed.

All functions prefer in-place writes and avoid extra allocations except when explicitly required (see Memory Contracts).

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> The append helpers keep the buffer nul-terminated to interoperate with legacy C string APIs used by shell components. Callers must still respect file-descriptor semantics when writing buffer contents to IO.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_buffer_append` / `ft_buffer_append_char` / `ft_buffer_append_str` | `NO` | Caller owns `t_buffer`; these functions mutate it in-place |
| `ft_buffer_to_string` | `YES` | Caller must `free()` the returned NUL-terminated copy |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - Passing `NULL` with a non-zero length to `ft_buffer_append` returns an error; passing `NULL` to `ft_buffer_append_str` returns silently.
> - Consumers relying on atomicity for multi-threaded access must add synchronization; these helpers are not thread-safe.
