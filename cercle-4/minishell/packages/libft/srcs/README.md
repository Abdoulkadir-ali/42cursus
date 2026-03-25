# 🗂️ Core Library Source Hub (`packages/libft/srcs`)

![Domain](https://img.shields.io/badge/Domain-Implementation_Matrix-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
The central repository for all raw C logic contained within `libft`. It structurally segregates the massive collection of primitive functions into 8 highly specific logical domains, preventing directory sprawl.

---

## ⚙️ Core Mechanic & Algorithms
**The Modular Assembly Sequence:**
1. The top-level `Makefile` systematically sweeps through these 8 domains.
2. Target `.o` object files are compiled in isolation (`ft_strlen.o`, `ft_printf.o`).
3. Object files are merged blindly into the `libft.a` static archive without any cross-domain coupling (e.g., `srcs/char/` never natively calls `srcs/lst/`).

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Norminette File Bounds:** Under the 42 School `Norminette` standard, no `.c` file may contain more than five individual functions. This drives the explicit hyper-fractionation seen within these source domains. Every major utility typically owns its own dedicated file (e.g., `ft_split.c`).

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Global Variable Ban:** No file within this source hub is permitted to mutate global state. All variables must be strictly local, or manually passed down as context structures (such as `t_list` tracking nodes).

---

## 🗂️ Internal Delegation
- **`base/`**: Hexadecimal, Binary, and Octal numerical conversions.
- **`char/`**: Standard scalar validation (`isalpha`, `isdigit`, etc.).
- **`fd/`**: OS-level descriptor manipulation extending into `get_next_line`.
- **`int/`**: Standard arithmetic translation (`atoi`).
- **`lst/`**: Complex Linked-List generation and structural iteration.
- **`mem/`**: Explicit memory-block mutations (`ft_memcpy`, `calloc`).
- **`printf/`**: Highly specialized variadic formatting wrappers.
- **`str/`**: Deep character-array manipulations (`split`, `join`, `trim`).
