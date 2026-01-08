# 🖨️ **ft_printf** - *Your Own Printf*

> **A Robust Reimplementation of the Standard C Library printf**
> Mastering variadic functions and formatted output parsing.

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Type](https://img.shields.io/badge/Type-Library-orange?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Stable-success?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-blue?style=for-the-badge)

---

## 📖 **Overview**

**ft_printf** is a comprehensive reimplementation of the standard `printf` function in C. This project delves deep into variadic functions (`stdarg.h`), structured parsing, and precise memory management. It supports a wide array of conversions, flags, widths, and precision settings, mimicking the behavior of the original function while serving as a fundamental building block for future C projects.

It provides a custom, lightweight, and efficient way to handle formatted output without relying on standard I/O libraries for formatting logic.

---

## ✨ **Key Features**

| Feature | Description |
| :--- | :--- |
| **🧩 Modular Architecture** | Clean separation between parsing logic, handlers, and printing utilities. |
| **🎭 Variadic Argument Handling** | Robust management of variable arguments using `va_list`. |
| **🏳️ Comprehensive Flag Support** | Handles combined flags like `#`, `SPACE`, `+`, `-`, and `0`. |
| **📏 Width & Precision** | Pixel-perfect alignment and formatting for numbers and strings. |
| **🔢 Multiple Conversions** | Supports characters (`c`), strings (`s`), pointers (`p`), integers (`d`, `i`), unsigned (`u`), and hex (`x`, `X`). |
| **⚙️ Buffer Management** | Optimized character output management. |

---

## 💻 **Supported Conversions**

| Specifier | Output Type | Example |
| :--- | :--- | :--- |
| `%c` | Single Character | `'a'` |
| `%s` | String of characters | `"Hello"` |
| `%p` | Pointer address | `0x7ffee4b` |
| `%d` / `%i` | Decimal (base 10) integer | `42` |
| `%u` | Unsigned decimal integer | `4294967295` |
| `%x` | Hexadecimal (base 16) lower | `2a` |
| `%X` | Hexadecimal (base 16) upper | `2A` |
| `%%` | Percent Sign | `%` |

---

## 🛠️ **Installation**

Integrate **ft_printf** into your C projects easily.

### **Prerequisites**
- **GCC / Clang** compiler
- **Make**

### **Build Instructions**

```bash
# 1. Clone the repository
git clone https://github.com/Abdoulkadir-ali/42cursus
cd cercle-2/printf

# 2. Compile the library
make

# 3. Use in your project
# gcc main.c -L. -lftprintf -o my_program
```

---

## 📝 **Usage**

Include the header and link the library to start using custom formatted output.

```c
#include "includes/ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s! The answer is %d.\n", "User", 42);
    ft_printf("Hex: %x, Ptr: %p\n", 255, &main);
    return (0);
}
```