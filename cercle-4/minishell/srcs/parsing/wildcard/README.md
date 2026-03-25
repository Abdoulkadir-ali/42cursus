# 🔬 Wildcard (Glob) Subpackage (`srcs/parsing/wildcard`)

![Domain](https://img.shields.io/badge/Domain-Filesystem_Pattern_Matching-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Responsible exclusively for interacting with the OS kernel (`opendir`, `readdir`) to match literal token strings containing active `*` or `?` wildcards against the current working directory. Yields a lexicographically sorted linked list of valid filename matches.

---

## ⚙️ Core Mechanic & Algorithms
**The Directory Evaluation Pipeline (`expand_wildcard`):**
1. Evaluates incoming token payload. If no active metacharacters (`*` or `?`) remain, returns instantly allowing the calling `env` layer to treat it literally.
2. Initiates `opendir(".")`.
3. Passes the directory stream to `collect_matches()`, which iteratively evaluates every file node via `readdir()`.
4. Normalizes pattern targets, comparing the extracted filename against the glob logic inside `check_entry()`.
5. Upon stream exhaustion, closes FD and runs `sort_list()` (an in-place Bubble Sort executing `ft_strcoll`) to organize results precisely the way Bash natively outputs them.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Dotfile Suppression Rules:** Standard globs (`*`) do NOT match hidden files (`.env`, `.git`). The `check_entry()` logic enforces that a file starting with `.` is instantly rejected *unless* the wildcard pattern itself explicitly begins with a literal dot (`.*`).

> [!NOTE]
> **Trailing Slash Matching:** A pattern ending in a slash (like `foo/*/`) strictly restricts matches to **directories only**. 

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Zero Matches Found** | Flushes directory stream safely. | Returns `NULL`. The upstream `env` parser automatically downgrades the `*` back into a literal payload. |
| **`opendir()` FD Failure** | Bypasses collection entirely. | Behaves identically to Zero Matches, ignoring silent OS blocks. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **In-Place Sort Swapping:** `sort_list()` swaps the physical `char *content` pointers inside the `t_nodes` struct instead of re-linking the list dynamically node-by-node. While stable for short filesystem returns, callers must not rely on memory address continuity for the exact payload of a given node during iterations!

---

## 🔌 API Signatures
```c
/**
 * @brief Expands glob patterns into a sorted linked list of disk matches.
 * @param pattern Raw token string harboring `*` or `?` logic.
 * @return Sorted `t_nodes *` representing localized file hits, or NULL.
 */
t_nodes	*expand_wildcard(char *pattern);
```