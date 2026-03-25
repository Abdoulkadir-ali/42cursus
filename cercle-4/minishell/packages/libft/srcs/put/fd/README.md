# 🔬 File Descriptor IO Subpackage (`packages/libft/srcs/fd`)

![Domain](https://img.shields.io/badge/Domain-Descriptor_Streams-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Maps memory onto physical OS streams. Implements robust wrappers around the standard `write()` system call and owns the highly-complicated `get_next_line` multiline buffering engine.

---

## ⚙️ Core Mechanic & Algorithms
**`get_next_line` (GNL) Buffering Schema:**
1. A static `char *buffer` persists across individual localized function calls.
2. `read(fd, buffer, BUFFER_SIZE)` pulls unformatted chunk streams from the kernel descriptor.
3. The engine scans the buffer for `\n` carriage returns. 
4. Valid lines are physically detached from the text block.
5. Remaining unread characters are explicitly shifted to the front of the static buffer, awaiting the next loop tick.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Descriptor Routing:** `ft_putstr_fd` replaces generic `printf`. While Standard Output (`1`) is default, Minishell heavily relies on feeding `STDERR` (`2`) natively into these `putendl` wrappers to ensure error alerts are not trapped horizontally inside command pipelines `|`.

---

## 💾 Memory Contracts (Critical)
| Function | Allocates | Freeing Responsibility |
| :--- | :--- | :--- |
| `ft_putstr_fd` | `NO` | Stateless kernel `write()` boundary. |
| `get_next_line()` | `YES` | Caller MUST `free()` every returned `<line>` pointer. Otherwise, memory leakage natively cascades. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Leaky Static Remnants:** Because `GNL` utilizes static internal variables, if code breaks off mid-read (e.g., executing a pipe `exit()`), the static variable contains orphaned `malloc` data. Proper descriptor teardown is natively enforced up the chain in Minishell's execution core to prevent valgrind leaks against `GNL`.
