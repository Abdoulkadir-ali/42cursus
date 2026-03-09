# Input Module

Handles all user input processing, segmentation, and reading logic for the shell. This subsystem is responsible for capturing, parsing, and preparing command lines for further parsing and execution.

---

## 📂 Directory Structure
- `srcs/input/` — Input processing root
  - `process/` — Segmentation and preprocessing of input lines
  - `reader/` — Interactive and multiline input reading, operations, and extenders

---

## 🏗️ How It Works

### `process/`
- **process.c**: Implements input segmentation logic. Splits raw input into command segments, handles chaining (e.g., `;`, `&&`, `||`), and prepares for tokenization.
- **segment.c**: Defines segment structures and helpers. Groups tokens into logical command segments.
- **utils.c**: Utility functions for segment manipulation, error handling, and context management.

#### Typical Flow
1. Raw input is received from the reader.
2. Segmentation functions split input into command segments.
3. Segments are passed to the parser/tokenizer for further processing.

---

### `reader/`
- **reader.c**: Main interactive input loop. Reads lines from the user, handles prompt display, and manages input history.
- **multiline.c**: Handles multiline input (e.g., unclosed quotes, heredoc). Ensures complete command lines before processing.
- **operations.c**: Implements input editing operations (e.g., cursor movement, deletion, insertion).
- **utils.c**: Helper functions for input reading, buffer management, and error recovery.
- **extenders/**: Extends input reading with additional features (e.g., custom prompt, advanced editing).

#### Typical Flow
1. Reader displays prompt and captures user input.
2. Handles multiline cases, ensuring input completeness.
3. Applies editing operations and passes input to segmentation.

---

## 🛠️ Developer Notes
- Input is always validated and segmented before parsing.
- Multiline and heredoc handling is robust to prevent incomplete commands.
- Editing operations are modular for easy extension.
- Utilities are file-local (`static`) where possible for clarity and safety.

For detailed function documentation, see the source files and header definitions in `includes/input.h` and submodule headers.
