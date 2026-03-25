# 🔬 AST Node Runners Subpackage (`srcs/exec/ast/exec`)

![Domain](https://img.shields.io/badge/Domain-Specific_Node_Drivers-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Contains the dedicated controllers for every Bash construct. Translates the recursive tree-walk logic into physical OS interactions (Pipes, Waits, Subshells, PATH discovery).

---

## ⚙️ Core Mechanic & Algorithms
**The Pipeline Setup (`exec_pipe`):**
1. Receives the AST Node marked `TOKEN_PIPE`.
2. Triggers an OS `pipe()` creating `fd[0]` and `fd[1]`.
3. Forks Child Left: Maps `STDOUT` to `fd[1]`, closes `fd[0]`, recurses `exec_tree(node->left)`.
4. Forks Child Right: Maps `STDIN` to `fd[0]`, closes `fd[1]`, recurses `exec_tree(node->right)`.
5. Parent strictly waits. Captures exit code uniquely from the *Right* child to propagate back.

**Logical Control (`exec_logical`):**
1. Recurses the `node->left` subtree fully. 
2. Evaluates the resulting exit code against the operator.
3. If `&&` and code `0`, or `||` and code `>0`, it executes `node->right`. Otherwise, it short-circuits.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **PATH Resolution Targeting:** Before calling `execve`, the node looks inside `$PATH`. Files inside this folder are matched. `find_path()` will reject matching targets that are physically Directories (throwing `is a directory`) or files stripped of `chmod +x` (throwing `Permission denied`).

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **Child Exits via Core Dump/Signal** | `handle_wait_status()` intercepts `WTERMSIG`. | Adjusts exit status to `128 + Signal_No` natively matching bash behaviors. |
| **Expansion Yields Zero Arguments** | Evaluator cleanly steps back (`expand.c`). | Returns `0`. Command execution silently aborts logic gracefully. |

---

## ⚠️ Edge Cases & Gotchas
> [!CAUTION]
> **Variable Assignments in Shell Context:** Assignments like `VAR=1 echo A` temporarily assign `$VAR` strictly for the lifecycle of that localized execution. `assignment.c` handles this by cloning the *entire* `state->envp` array, appending the variable, executing, and physically unwinding everything back independently.

---

## 🗂️ Internal Delegation
- **`simple/`**: Drives terminal `TOKEN_WORD` targets deciding between External vs Builtins.
- **`redirection/`**: Drives `TOKEN_RED_IN` / `TOKEN_RED_OUT` file binds.
