# 📚 Core Utilities Library (`packages/libft/`)

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Build](https://img.shields.io/badge/Build-Static%20Archive-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Ultra_Detailed-success?style=for-the-badge)

---

## 🏗️ Architecture TL;DR
> **The fundamental building blocks.**  
> `libft` is a comprehensive recreation of the C Standard Library, expanded with custom linked-list drivers, advanced formatting (`printf`), and resilient string manipulation utilities. It operates entirely statically and statelessly, assuming no knowledge of Minishell's specific AST or signal handlers.

---

## 🗺️ Build Compilation Flow
```mermaid
stateDiagram-v2
    [*] --> Make
    
    state Make {
        compile_objects: cc -c *.c
        archive: ar rcs libft.a *.o
        compile_objects --> archive
    }
    
    state Object_Generation {
        base: Number bases
        char: Ascii checks
        fd: I/O + GNL
        lst: Linked Lists
        mem: RAM blocks
        printf: Variardic strings
        str: String splits
    }
    
    Object_Generation --> compile_objects: Includes all subpackages
    
    archive --> [*]: Yields libft.a
```

---

## 🧱 Subsystems Matrix
| Subsystem | Core Responsibility | Primary Data Structure |
| :--- | :--- | :--- |
| **`includes/`** | The API Surface | Defines `t_list` natively. |
| **`srcs/base/`** | Number Conversions | `long long` logic. |
| **`srcs/char/`** | ASCII Identifiers | `char` bounds checking. |
| **`srcs/fd/`** | Descriptor I/O | `get_next_line` buffers. |
| **`srcs/int/`** | Integer Arithmetic | Parsing arrays cleanly. |
| **`srcs/lst/`** | List Iterations | `t_list` traversals. |
| **`srcs/mem/`** | RAM copying | `void *` shifting. |
| **`srcs/printf/`** | Formatted Data | Variadic `va_list` parsing. |
| **`srcs/str/`** | String Mutations | Deep `char **` allocations. |
| **`srcs/buffer/`** | Dynamic buffer builder | `t_buffer` growing byte buffer |

Additional grouped data primitives live under `srcs/data/` (e.g. `srcs/data/buffer`, `srcs/data/stack`, `srcs/data/lst`) and consolidate small one-responsibility modules for easier Norminette compliance and review.

---

## 🧠 Global Memory Strategy
Because `libft` is stateless:
- **Zero Globals:** No global variables are permitted (excluding implicit static buffers localized purely in `get_next_line`).
- **Transfer of Ownership:** Any function returning an allocated pointer (e.g. `ft_split`, `ft_strjoin`, `ft_itoa`) strictly **hard-transfers ownership** to the caller. The caller MUST trigger `free()`.
- **In-Place Mutation:** Functions like `ft_bzero` or `ft_strlcpy` mutate memory bounded entirely by the caller.

---

## 🛡️ Error & Safety Philosophy
> [!IMPORTANT]
> **Defensive Pointer Guards:** Unlike standard `libc` functions which often Segfault gracefully, `libft` natively wraps execution blocks with defensive `if (!ptr)` guards where applicable, ensuring graceful `NULL` returns.

> [!CAUTION]
> **Strict Norminette Compliance:** The entire architecture is restricted to 25-line functions and maximum variable counts, forcing extreme code decoupling.
