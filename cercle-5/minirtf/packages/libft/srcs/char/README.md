# 🔬 Character Assertions Subpackage (`packages/libft/srcs/char`)

![Domain](https://img.shields.io/badge/Domain-ASCII_Scalars-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Handles extreme high-speed primitive boolean checks against single `char` inputs to validate ASCII standard mappings (e.g. "Is this a number?", "Is this an alphabetical character?").

---

## ⚙️ Core Mechanic & Algorithms
**Primitive Boolean Returns:**
Rather than generating complex objects, all functions operate mathematically against the 0-127 standard ASCII scalar table.
`ft_isalpha(c)` literally queries: `if (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')`
This bypasses the need for large string comparison checks natively, completing operations strictly in $O(1)$ constant time.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Integer Overload:** Standard libc `isalpha` and `isdigit` accept type `int` rather than `char` explicitly to handle `<EOF>` constants correctly. This `libft` mimic matches that exact POSIX constraint, accepting `int` wrappers to prevent type-truncation bugs in reader loops.

---

## 💾 Memory Contracts (Critical)
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| **All Functions** | `NO` | Completely stateless execution paths. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Extended ASCII Exclusion:** These checks explicitly target standard US-ASCII bounds. If `UTF-8` or extended Arabic/Cyrillic unicode buffers (`>127`) are passed in, functions explicitly return `0` (False).
