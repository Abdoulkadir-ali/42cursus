# 🔬 Integer Parsers Subpackage (`packages/libft/srcs/int`)

![Domain](https://img.shields.io/badge/Domain-String_Mathematical_Extraction-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Converts human-readable ASCII matrices (`char *`) cleanly into native hardware integers (`long long`, `int`). 

---

## ⚙️ Core Mechanic & Algorithms
**The `atoi` Extractor Loop:**
1. Strips leading whitespace constraints strictly according to `ft_isspace`.
2. Intercepts `+` or `-` polarity markers.
3. Multiplicatively shifts numerical limits: `res = (res * 10) + (*str - '0')`.
4. Disregards trailing alphabetic characters intrinsically.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Max Bounds Override:** While `ft_atoi` returns a standard physical `int`, shell variables often massively overflow 32-bit capabilities. `ft_atoll` leverages maximum `long long` bounds natively to securely intercept `$?` shell limit overloads and large `exit` numeric markers safely.

---

## 💾 Memory Contracts (Critical)
| Function | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_atoi` | `NO` | Completely stack-bound $O(N)$ execution path. |
| `ft_safe_atoll` | `NO` | Emits physical boolean failures entirely cleanly. |

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Integer Overflow** | `ft_safe_atoll` hits architecture boundaries during iteration. | Cancels parsing physically. Sets error state. Returns flag blocking Bash `exit` assignments natively. |
