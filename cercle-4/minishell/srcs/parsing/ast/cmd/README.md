# 🔬 Command AST Helpers Subpackage (`srcs/parsing/ast/cmd`)

![Domain](https://img.shields.io/badge/Domain-Command_Node_Extraction-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Responsible exclusively for peeling a linear sequence of tokens representing a *single pipeline segment* into a finalized `t_ast` command node. It counts words, extracts leading variable assignments (prefixes), allocates the exact `argv` array size, and safely manages allocations if the process is interrupted.

---

## ⚙️ Core Mechanic & Algorithms
**The Simple Command Extraction Algorithm:**
1. **Scanning (`scanner.c`):** Iterate the token list until `TOKEN_PIPE` or `NULL`. Variables are counted:
   - Calculate how many words exist (`cmd->count`).
   - Calculate how many leading variable assignments exist *before* the first word (`cmd->prefix_count`).
2. **Prefix Collection (`collect.c`):** Allocate `char **assigns`. Duplicate up to `prefix_count` via `ft_strdup`.
3. **Arg Collection (`collect.c`):** Allocate `char **args` based on `cmd->count`. Copy legitimate words (skipping tokens immediately succeeding redirection operators, as they are filenames).
4. **Redirection Binding:** Invoke `process_redirections()` to consume `<` / `>` syntax.
5. **Finalization (`finalize.c`):** Pack arrays into a `t_ast` block, tagging `node->is_quoted` if wildcard protection was declared.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Prefix Assignment Binding:** In Bash, `VAR=1 echo hello` temporarily injects `VAR` into the environment for `echo`. The scanner actively differentiates between a *prefix* (assigned before the first word) and an *argument* (assigned after the first word). Any `TOKEN_PREFIX` found after a valid `TOKEN_WORD` is purposefully demoted and collected into the command's `argv` array instead of `assigns`.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`malloc()` failure during `ft_strdup`** | Instantly breaks loop. Runs `free()` on partially filled `args` / `assigns`. | Returns `NULL`. Cascades up to `build_ast`, safely aborting the AST execution pipeline without memory bloat. |
| **Zero Words Scanned (`cmd.count == 0`)** | Skips `argv` allocation entirely. | Command node acts purely as an environment mutator or flat redirection executor (e.g., `> file.txt`). |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Redirection Target Ghosting:** The collector algorithms (`build_args_from_tokens`) must explicitly detect `TOKEN_REDIR` and intentionally skip iterating the immediately following token. Failing to do this causes the redirection filename to bleed accidentally into the command's `argv` matrix as an executable parameter.

---

## 🔌 API Signatures
```c
/**
 * @brief Constructs a finalized AST command node from raw contiguous pipeline tokens.
 * @param tokens Linked list of unparsed pipeline tokens.
 * @return Fully allocated `t_ast *` command node, or NULL on intense memory pressure.
 */
t_ast	*handle_simple_cmd(t_nodes *tokens);
```
