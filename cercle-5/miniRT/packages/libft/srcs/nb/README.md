# 🧮 Number Utilities Subpackage (`packages/libft/srcs/nb`)

![Domain](https://img.shields.io/badge/Domain-Numeric_Primitives-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Deterministic-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Small, well-tested helpers for integer and base conversions, digit counting and base-aware formatting helpers used by higher-level printing and parsing code.

---

## ⚙️ Core Mechanic & Algorithms
- `ft_count_digits(n)` and `ft_count_hex_digits(n)` compute digit counts by repeated division — constant auxiliary memory and $O()$ time proportional to digit count.
- Base conversions (`ft_itoa_base`, `ft_itoa`) build results into pre-sized buffers using counts computed beforehand to avoid reallocations.

All routines prefer simple integer arithmetic rather than string-based scanning to remain predictable and efficient.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> Functions accept and return plain C integer types matching POSIX expectations (e.g., `int`, `long`, `unsigned long`) to interoperate cleanly with `read` loops and printf-like APIs.

---

## 💾 Memory Contracts
| Domain | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_itoa*` family | `YES` | Caller must `free()` the returned string |
| Counting helpers | `NO` | Stateless returns |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> - `ft_itoa` behavior with `INT_MIN` mirrors standard `itoa` style handling; callers should consider signed edge cases.
> - Base conversion expects valid base strings; invalid base arguments are undefined behavior.
