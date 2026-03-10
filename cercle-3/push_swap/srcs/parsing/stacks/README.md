# Stack Parsing Module

This directory contains the code that validates numeric input and constructs the
runtime stack state. In the current `push_swap` flow, this package is the input
construction layer: it checks whether user-provided values are valid integers,
rejects duplicates, builds nodes, and prepares the `t_stacks` structure used by
the rest of the project.

The implementation here is spread across a few focused files:

- `parser.c` builds stacks from argument strings
- `parse_int.c` converts numeric text into a validated integer value
- `check.c` provides validation helpers for duplicates and numeric form
- `free.c` releases both stacks through one shared helper
- `main.c` contains a checker-oriented standalone entry flow for this parsing package

## Stack Initialization Path

`init_stacks` in `parser.c` is the main entry point for building the runtime
stacks from an array of strings.

The full flow is:

1. Reset stack `a`, stack `b`, and the verbose flag.
2. Walk through every input string in the provided array.
3. Call `process_string` for each one.
4. If any call fails, clear stack `a`, reset it to `NULL`, and stop.

This means the function supports both already split argument arrays and larger
strings that still need internal splitting.

## String Processing Path

`process_string` in `parser.c` handles one raw argument string.

The steps are:

1. Split the string on spaces with `ft_split`.
2. Return `-1` immediately if splitting fails.
3. Pass the resulting tokens to `add_numbers_from_split`.
4. Free the temporary split array with `ft_free_split`.
5. Return the result.

This helper isolates temporary token management from the outer stack-building
loop.

## Token Insertion Path

`add_numbers_from_split` in `parser.c` performs the real stack-building work.

The full flow is:

1. Walk through the split token array.
2. Skip empty tokens.
3. Parse the token with `parse_int`.
4. Stop with failure if parsing reports an error.
5. Reject the value if `is_duplicate` finds it in stack `a`.
6. Allocate a new node with `ft_new`.
7. Stop with failure if allocation fails.
8. Append the node to stack `a` with `ft_add_back`.

This is the point where raw numeric text becomes actual nodes in the circular
stack structure.

## Integer Parsing Path

`parse_int` in `parse_int.c` is the safe numeric conversion entry point.

The steps are:

1. Reset the error flag.
2. Parse the sign sequence with `parse_sign`.
3. Parse the digit sequence with `parse_digits`.
4. Reject extra trailing characters.
5. Apply the sign.
6. Validate that the result fits in the `int` range.

If any step fails, the function sets the error flag and returns `0`.

## Sign Parsing Path

`parse_sign` in `parse_int.c` handles leading `+` and `-` characters.

The important behavior is:

- it accumulates the sign while consuming sign characters
- it counts how many sign characters were seen
- it can reject multiple signs when `MULTIPLE_SIGN_INVALID` is enabled

This makes the parser stricter than a basic `atoi`-style conversion and keeps
the accepted input format explicit.

## Digit Parsing And Range Path

`parse_digits` in `parse_int.c` is responsible for reading the numeric body of
the token.

The steps are:

1. Reject the input if the first remaining character is not a digit.
2. Convert digit characters one by one.
3. Detect overflow before multiplying and adding the next digit.
4. Stop on the first non-digit character.

`validate_range` then checks whether the signed result fits inside the `int`
limits expected by the project.

## Validation Helper Path

`check.c` provides three helpers used by stack creation and validation:

- `has_duplicates` scans a full stack for duplicate values
- `is_duplicate` checks whether one value already exists in a stack
- `ft_isnum` validates whether a string is made of optional whitespace, sign characters, and digits

These helpers keep the main parser code shorter and separate the validation
rules from the construction logic.

## Cleanup Path

`free_stacks` in `free.c` frees both runtime stacks by delegating to `ft_clear`.

This gives the parsing and checker flows one shared cleanup entry point when
stack construction must be abandoned or the program is done.

## Standalone Checker Flow

`main.c` in this directory contains a small checker-style executable flow built
around the same parsing helpers.

Its main responsibilities are:

- initialize stacks from command-line arguments
- read instructions from standard input
- execute them through `execute_instruction`
- print `OK` or `KO`
- free the final stack state

That file sits slightly above pure parsing, but it still belongs here because it
demonstrates and reuses the stack initialization and instruction-processing
paths provided by this package.

## Folder-Level Call Chains

The main function chains in this subtree are:

1. `init_stacks` -> `process_string` -> `add_numbers_from_split` -> `parse_int`
2. duplicate check path -> `add_numbers_from_split` -> `is_duplicate`
3. integer conversion path -> `parse_int` -> `parse_sign` -> `parse_digits` -> `validate_range`
4. cleanup path -> `free_stacks` -> `ft_clear`

## Practical Role In The Project

The stack parsing module is what turns user input into a valid initial runtime
state. Without it, the algorithm would have no trustworthy stack to operate on,
and the checker would have no correct starting point to validate.

That makes this folder one of the project’s most important correctness gates:
it enforces numeric validity, uniqueness, and structural integrity before the
rest of the runtime takes over.