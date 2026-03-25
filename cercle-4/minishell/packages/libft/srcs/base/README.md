# 🔬 Base Converters Subpackage (`packages/libft/srcs/base`)

![Domain](https://img.shields.io/badge/Domain-Numeric_Bases-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Handles arbitrary mathematical conversion between numeric base strings (Binary `01`, Octal `0-7`, Decimal `0-9`, Hexadecimal `0-F`).

---

## ⚙️ Core Mechanic & Algorithms
**The Base Divisor Schema:**
Instead of hardcoding hexadecimal or octal arrays natively, the functions accept arbitrary `char *base` strings. 
1. `ft_check_base()` universally asserts the provided base is valid (no duplicate characters, no `+` or `-` math symbols).
2. The integer length is determined via `ft_nbrlen_base()`, calculating string size natively using the base length as the divisor loop constraint.
3. Actual output operations mathematically isolate integers via `num % root`.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Base 10 Assumptions:** Standard C `atoi` strictly assumes Decimal. These custom `.c` generators remove that constraint, fully allowing bitwise or hexadecimal translations entirely in-memory without `#include <math.h>` operations.

---

## 💾 Memory Contracts (Critical)
| Function | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_itoa_base()` | `YES` via `malloc` | Caller MUST call `free()` on returned string. |
| `ft_putnbr_base()` | `NO` | Prints directly to `fd(1)`. No heap interaction. |
