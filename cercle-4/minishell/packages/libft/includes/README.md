# 🗂️ Core Library Headers (`packages/libft/includes`)

![Domain](https://img.shields.io/badge/Domain-Static_Prototypes-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
This directory exclusively tracks the structural bounds and functional prototypes for `libft`. It exposes precisely *what* functions the library provides to Minishell, hiding the raw C logic behind pristine interface contracts.

---

## ⚙️ Core Mechanic & Algorithms
**Static API Linking:**
1. The developer `#include "libft.h"` within their standard `srcs/` files.
2. The header provides immediate C pre-processor access to core structs, notably `t_list`, preventing nested definitions.
3. Upon compilation, the headers satisfy the `-Wall -Wextra -Werror` flags by pre-defining all `ft_*` signatures before the linker resolves them against the final `libft.a` binary.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Namespace Collisions:** To entirely avoid colliding with actual `libc` function signatures natively provided by `<string.h>` or `<stdlib.h>`, every single API exposed here is strictly prefixed with `ft_` (e.g., `ft_strlen`, not `strlen`).

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Missing Declaration** | Compiler intercepts via `-Werror`. | Build halts entirely. Linker never invoked. |
| **Data Structure Mutation** | Redefining `t_list` natively. | Emits multiple definition errors blocking compilation. |

---

## 🗂️ Internal Delegation
- **`libft.h`**: The sole unified entry point bridging all 8 subpackage capabilities (Lists, Printf, Strings, Mem, etc.) into a singular include command.
