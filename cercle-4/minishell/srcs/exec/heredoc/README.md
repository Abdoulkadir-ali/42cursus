# 🔬 Heredoc Processing Subpackage (`srcs/exec/heredoc`)

![Domain](https://img.shields.io/badge/Domain-Interactive_Temp_IO-1f6feb?style=for-the-badge)
![Strictness](https://img.shields.io/badge/Strictness-Maximum-critical?style=for-the-badge)

---

## 🎯 Specific Domain
Responsible for freezing execution to interactively read multiline user payloads triggered by `<<`. Manages delimiter quoting logic, generates protected temporary files in the kernel OS cache (`/tmp/`), and acts as a pre-execution barrier ensuring all heredocs are materialized *before* the first command in a pipeline forks.

---

## ⚙️ Core Mechanic & Algorithms
**The Payload Manifestation Loop (`scan_heredocs` & `handle_heredoc_input`):**
1. An AST is recursively swept *prior* to `fork()` to locate all `<<` redirections.
2. The exact Delimiter is extracted. 
   - If the original token was quoted (`"EOF"` or `'EOF'`), `is_quoted_delim()` marks it so the eventual read loop **skips** variable `$VAR` expansion natively.
3. `generate_tmp_filename()` asks the kernel for a secure, localized `char *` path inside `/tmp/`.
4. `read_heredoc_loop()` begins:
   - Identifies if `STDIN` is a TTY (interactive `readline` prompt) or PIPED (raw `get_next_line`).
   - Gathers strings until a strict `ft_strcmp(line, delimiter) == 0` hits.
5. Emits the written temporary file path back to the AST Node for future `dup2()` execution bindings.

---

## 📜 POSIX & Shell Compliance
> [!IMPORTANT]
> **Pre-Execution Spooling:** Bash natively processes all heredocs in a pipeline **first**. If `cat << EOF | sleep 5` is run, the prompt for `EOF` occurs *before* the `sleep` timer starts. `scan_heredocs()` enforces this exact sequencing by iterating the AST broadly before `exec_tree()` executes deeply.

> [!CAUTION]
> **Delimiter Evaluation:** `<< $USER` dynamically evaluates the delimiter string if unquoted, making the runtime required sequence `<< abdoali` not literal `$USER`.

---

## 🚨 Error & Signal Propagation
| Condition | Immediate Action | Upstream Impact |
| :--- | :--- | :--- |
| **`SIGINT` (Ctrl+C) hits** | Updates `g_last_signal`. Preempts `readline()`. | Aborts the heredoc loop. File creation is canceled, returning `NULL` back to AST causing execution to abort silently with exit code `130`. |
| **Unexpected EOF (Ctrl+D)** | Loop completes normally. Emits standard formatting warning: `warning: here-document delimited by end-of-file`. | The captured payload is written securely up to the abort point. Execution continues normally. |

---

## ⚠️ Edge Cases & Gotchas
> [!WARNING]
> **Temporary File Clogging (Unlinking):** Because Minishell translates heredocs into physical disk memory, these `/tmp/` files must be rigorously tracked and `unlinked()` safely by the core execution shutdown logic, otherwise prolonged terminal usage will clog physical storage capacity.

---

## 🔌 API Signatures
```c
/**
 * @brief Top-Level AST pre-processor manifesting heredocs into file paths.
 * @param ast The root node of an unexecuted parsed AST.
 * @param state Global shell states passing local environment for expansion.
 */
void	scan_heredocs(t_ast *ast, t_shell_state *state);
```
