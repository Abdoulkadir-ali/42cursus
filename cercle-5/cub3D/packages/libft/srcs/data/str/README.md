# 🔬 High-Level String Mutator Subpackage (`packages/libft/srcs/str`)

![Domain](https://img.shields.io/badge/Domain-Char_Array_Logic-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Replicates physical C boundaries targeting deep formatting bounds across raw strings (`char *`). Owns generation matrices that split input arrays logically based directly around targeted delimiter tokens.

---

## ⚙️ Core Mechanic & Algorithms
**`ft_split` Vectorization Engine:**
1. Tracks linearly over `char *str`.
2. Locates target delimiter barriers structurally explicitly parsing logical words.
3. Computes extreme structural bounds executing early `malloc` invocations representing massive `char **` 2D Array buffers.
4. Substrings individual arrays physically creating completely standalone Heap environments divorced from the original memory string block.

**`ft_strjoin` Appendment Wrappers:**
1. Dynamically reads `A_length` and `B_length`.
2. Allocates brand new arrays representing `A_length + B_length + 1`.
3. Pushes generic block memory directly to formulate massive text sequences flawlessly tracking `\0` markers natively natively mimicking Python string interpolations.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Truncation Bounds Guarding:** `ft_strlcpy` securely guarantees truncation boundaries heavily preventing accidental string overlaps (Buffer Overruns). Native `strcpy` inherently explodes terminal boundaries natively causing mass data leaks. This explicitly enforces POSIX-approved structural truncation arrays ensuring all targets explicitly lock themselves automatically trailing with a mandatory `\0`.

---

## 💾 Memory Contracts (Critical)
| Function | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_split` / `ft_strdup` | `YES` | Directly translates block matrices to the user requiring rigorous explicit Free protocols traversing 2D matrices independently. |
| `ft_strchr` / `ft_strlen` | `NO` | Stateless Read-only pointers. |
