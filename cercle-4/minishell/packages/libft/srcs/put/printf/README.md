# 🔬 Variadic Formatter Subpackage (`packages/libft/srcs/printf`)

![Domain](https://img.shields.io/badge/Domain-Variadic_String_Output-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Custom static reimplementation of the immense `sprintf`/`printf` formatting boundary. Heavily targets generic struct formatting logging outputs directly to custom OS descriptors or STDOUT.

---

## ⚙️ Core Mechanic & Algorithms
**The Format Parsing Loop (`ft_printf.c`):**
1. An unknown number of arguments are stacked using `<stdarg.h>` structures (`va_list`).
2. Iterates natively across the format string literal until intercepting exactly a `%` modifier token.
3. Invokes `ft_parse_flags` isolating integer sizes or generic string references.
4. Diverts execution immediately to custom domain translators (`ft_handle_pointer`, `ft_handle_hex`).
5. Translates logical payloads and pushes characters explicitly back into the underlying Write buffers.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Null Pointer Failsafes:** Natively, attempting to format a purely `NULL` string variable into a normal POSIX `%s` triggers an immediate terminal `SEGFAULT` crashing the shell. This custom wrapper explicitly guards against crashes, writing `(null)` dynamically back into the console streams instead of initiating Core Dumps.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| **All Formatting Writers** | `NO` | Zero internal structural tracking strings. Everything executes blindly into `fd(1)` output streams instantly avoiding all heap requests. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Return Metrics Bound Failures:** `printf` inherently outputs the strictly tracked integer sum mapping every single byte pushed through `write()`. If the underlying `write()` OS connection experiences failure (`-1`), the tracker halts mapping explicitly preventing false log records.
