import sys
import os
import re

DOCS = {
    "ft_atoi": "Converts the initial portion of the string pointed to by str to int representation.",
    "ft_bzero": "Erases the data in the n bytes of the memory starting at the location pointed to by s by writing zeros.",
    "ft_calloc": "Allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allocated memory.",
    "ft_isalnum": "Checks for an alphanumeric character; it is equivalent to (isalpha(c) || isdigit(c)).",
    "ft_isalpha": "Checks for an alphabetic character; in the standard 'C' locale, it is equivalent to (isupper(c) || islower(c)).",
    "ft_isascii": "Checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.",
    "ft_isdigit": "Checks for a digit (0 through 9).",
    "ft_isprint": "Checks for any printable character including space.",
    "ft_itoa": "Allocates (with malloc) and returns a string representing the integer received as an argument. Negative numbers must be handled.",
    "ft_memchr": "Scans the initial n bytes of the memory area pointed to by s for the first instance of c.",
    "ft_memcmp": "Compares the first n bytes of the memory areas s1 and s2.",
    "ft_memcpy": "Copies n bytes from memory area src to memory area dest. The memory areas must not overlap.",
    "ft_memmove": "Copies n bytes from memory area src to memory area dest. Handles overlap securely.",
    "ft_memset": "Fills the first n bytes of the memory area pointed to by s with the constant byte c.",
    "ft_putchar_fd": "Outputs the character c to the given file descriptor.",
    "ft_putendl_fd": "Outputs the string s to the given file descriptor, followed by a newline.",
    "ft_putnbr_fd": "Outputs the integer n to the given file descriptor.",
    "ft_putstr_fd": "Outputs the string s to the given file descriptor.",
    "ft_split": "Allocates (with malloc) and returns an array of strings obtained by splitting s using the character c as a delimiter.",
    "ft_strchr": "Returns a pointer to the first occurrence of the character c in the string s.",
    "ft_strdup": "Returns a pointer to a new string which is a duplicate of the string s.",
    "ft_striteri": "Applies the function f to each character of the string passed as argument, and passes its index as first argument.",
    "ft_strjoin": "Allocates and returns a new string, which is the result of the concatenation of s1 and s2.",
    "ft_strlcat": "Size-bounded string concatenation. Appends string src to the end of dst ensuring NUL-termination.",
    "ft_strlcpy": "Size-bounded string copying. Copies up to dstsize - 1 characters from the string src to dst.",
    "ft_strlen": "Computes the length of the string s.",
    "ft_strmapi": "Applies the function f to each character of the string s to create a new string mapped iteratively.",
    "ft_strncmp": "Compares the two strings s1 and s2 up to n bytes.",
    "ft_strnstr": "Locates the first occurrence of the null-terminated string little in the string big.",
    "ft_strrchr": "Returns a pointer to the last occurrence of the character c in the string s.",
    "ft_strtrim": "Allocates and returns a copy of s1 with the characters specified in set removed from both ends.",
    "ft_substr": "Allocates and returns a substring from the string s. The substring begins at index start and is of maximum size len.",
    "ft_tolower": "Converts an uppercase letter to lowercase.",
    "ft_toupper": "Converts a lowercase letter to uppercase.",
    "ft_lstnew": "Allocates and returns a new tracking node.",
    "ft_lstadd_front": "Adds a struct node at the beginning of the list.",
    "ft_lstsize": "Counts the total physical number of nodes in a linked list.",
    "ft_lstlast": "Iterates and returns the isolated last node of the list.",
    "ft_lstadd_back": "Adds a struct node at the end of the list.",
    "ft_lstdelone": "Takes a node and frees the memory of its content using the provided pointer function.",
    "ft_lstclear": "Deletes and frees the given node and every downstream successor organically.",
    "ft_lstiter": "Iterates the list and strictly applies a function block on the content of each node.",
    "ft_lstmap": "Iterates the list and maps a functional wrapper against each node generating a brand new list.",
    "ft_printf": "Outputs a formatted string to stdout by parsing variadic arguments.",
    "get_next_line": "Reads a single line comprehensively from an active file descriptor natively mapping static buffers."
}

def get_desc(name):
    if name in DOCS: return DOCS[name]
    if "is" in name and "ft_" in name: return f"Evaluates if input satisfies {name.replace('ft_is', '')} conditions natively."
    if "put" in name: return "Outputs formatted data explicitly to the targeted descriptor/stdout."
    if "mem" in name: return "Performs raw physical memory block operations dynamically."
    if "str" in name: return "Performs structural string manipulations or deep traversal inspections."
    if "lst" in name: return "Executes linked-list structural operation across memory nodes."
    if "printf" in name: return "Internal variadic formatting string generator proxy."
    if "base" in name: return "Architectural mathematical conversion enforcing numerical bases."
    return f"Executes the public {name} utility operation."

def process_file(filepath):
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    lines = content.split('\n')
    new_lines = []
    
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Identify typical 42 C function bounding logic: `type (tabs/spaces) func_name(args)` followed by `{`
        if i + 1 < len(lines) and lines[i+1].startswith('{') and '(' in line and ')' in line and not line.endswith(';'):
            # Disregard private static logic
            if line.startswith('static '):
                new_lines.append(line)
                i += 1
                continue
                
            sig_match = re.search(r'^([A-Za-z0-9_\s\*]+?)\s+([A-Za-z0-9_]+)\s*\(([^)]*)\)', line.strip())
            if sig_match:
                ret_type = sig_match.group(1).strip()
                func_name = sig_match.group(2).strip()
                args_str = sig_match.group(3).strip()
                
                # Deep extraction of explicitly named variables filtering Pointer * symbols
                params = []
                if args_str and args_str != "void":
                    for arg in args_str.split(','):
                        arg = arg.strip()
                        if arg:
                            parts = re.split(r'[\s\*]+', arg)
                            param_name = parts[-1]
                            if not param_name:
                                match = re.search(r'([a-zA-Z0-9_]+)$', arg.replace('*',' ').strip())
                                if match: param_name = match.group(1)
                            if param_name and param_name != "void" and param_name != "...":
                                params.append(param_name)
                            elif param_name == "...":
                                params.append("variadic_args")
                
                # Check for existing Doxygen implementation
                has_doc = False
                check_idx = len(new_lines) - 1
                while check_idx >= 0 and new_lines[check_idx].strip() == '':
                    check_idx -= 1
                if check_idx >= 0 and new_lines[check_idx].strip() == '*/':
                    has_doc = True
                    
                if not has_doc:
                    doc_block = [
                        "/**",
                        f" * @brief {get_desc(func_name)}",
                        " * "
                    ]
                    
                    if params:
                        for p in params:
                            doc_block.append(f" * @param {p} Target structural variable.")
                    else:
                        doc_block.append(" * @param void No arguments required.")
                        
                    if ret_type == "void":
                        doc_block.append(" * @return void (Stateless void execution).")
                    else:
                        # Clean multiple spaces or tabs inside ret_type mapping
                        clean_ret = re.sub(r'\s+', ' ', ret_type)
                        doc_block.append(f" * @return {clean_ret} output natively.")
                        
                    doc_block.append(" */")
                    new_lines.extend(doc_block)
            
            new_lines.append(line)
            i += 1
            continue
            
        new_lines.append(line)
        i += 1

    with open(filepath, 'w', encoding='utf-8') as f:
        f.write('\n'.join(new_lines))


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 doc_injector.py [TARGET_DIR]")
        sys.exit(1)
        
    target_dir = sys.argv[1]
    print(f"Running heavily-detailed automated Doxygen injection mapping Native variables on {target_dir}")
    count = 0
    for root, dirs, files in os.walk(target_dir):
        for fl in files:
            if fl.endswith('.c'):
                try:
                    process_file(os.path.join(root, fl))
                    count +=1
                except Exception as e:
                    print(f"Error on {fl}: {e}")
    print(f"Successfully processed and mapped {count} C files.")
