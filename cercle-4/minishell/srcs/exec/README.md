# 🧭 Execution Subsystem (`srcs/exec`)

![Language](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Subsystem](https://img.shields.io/badge/Subsystem-Kernel_Runtime_Interfacing-1f6feb?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Ultra_Detailed-success?style=for-the-badge)

---

## 🏗️ Architecture TL;DR
> The Execution Subsystem represents the physical "Action Phase" of Minishell. Where the `parsing/` module is strictly analytical and read-only, `exec/` interacts forcefully with the Linux kernel. It spawns child processes (`fork`), manipulates file descriptors (`dup2`), scans the mapped disk for executables (`execve`), and dynamically rewrites the live memory bounds of the shell's active environment matrix.

---

## 🗺️ Data Flow Diagram
```mermaid
stateDiagram-v2
    [*] --> AST_Ingestion: Valid t_ast *root
    
    state AST_Ingestion {
        heredoc: scan_heredocs()
        exec: exec_tree()
        heredoc --> exec: Pre-Execution Spooling
    }
    
    AST_Ingestion --> Runtime_Layer
    
    state Runtime_Layer {
        builtins: exec/builtins/
        external: OS fork() + execve()
        env: exec/env/ Modifier
        
        exec --> builtins: is_builtin() == true
        exec --> external: is_builtin() == false
    }
    
    builtins --> env: Mutates state->envp natively
    external --> waitpid: Parent monitors child exit
    
    env --> [*]
    waitpid --> [*]: Normalizes WEXITSTATUS
```

---

## 🧱 Subsystems Matrix
| Subsystem | Core Responsibility | Consumes | Produces |
| :--- | :--- | :--- | :--- |
| **`heredoc/`** | Pre-Execution materialization. | `<<` AST Nodes | Physical `/tmp/` files buffering multiline input. |
| **`ast/`** | The execution router. | `t_ast *root` | Triggers OS forks, Pipes, and Logical operators. |
| **`builtins/`** | Internal Command execution. | `char **args` | Mimics specific binaries locally (e.g. `cd`, `export`). |
| **`env/`** | Structural memory shifting. | `envp` Array | Safely re-allocating environment matrices during `unset`/`export`. |

---

## 🧠 Global State Strategy
The `exec` module is the **only subsystem in Minishell** permitted to deeply mutate global state during successful operation:
- Changes to `$PWD` / `$OLDPWD` are physically manifested here.
- `state->exit_code` is consistently overwritten based on `waitpid()` normalizations mapping from `WIFEXITED` limitations into simple integers (0-255).
- Internal variable prefixes natively attached to simple commands (e.g., `VAR=1 ls`) trigger localized duplicates of `state->envp` entirely contained within the execution lifetime of that leaf node.

---

## 🛡️ Error & Signal Philosophy
> [!NOTE]
> **Signal Context Shifting:** The Execution module aggressively alters signal handlers dynamically. When `readline()` is prompting, `SIGINT` creates a new line. When a heredoc is prompting, `SIGINT` aborts the `/tmp/` file. When an external binary is running, `SIGINT` is completely ignored by the parent Minishell and passed entirely to the child `cat`. Each state shift is managed natively during the setup of the respective OS action.
