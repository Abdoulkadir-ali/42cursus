#!/usr/bin/env python3
"""
Convert `struct s_name { ... };` to `typedef struct s_name { ... } t_name;` in a C header.
Usage: ./scripts/convert_structs.py path/to/includes/objects.h
Writes modified file in-place, saving a backup with .bak extension.
"""
import sys
import re

def convert_structs(text):
    # Find occurrences of `struct s_name {` and match the brace-balanced block
    pattern = re.compile(r'\bstruct\s+(s_[A-Za-z0-9_]+)\s*\{', re.M)
    out = []
    pos = 0
    while True:
        m = pattern.search(text, pos)
        if not m:
            out.append(text[pos:])
            break
        start = m.start()
        name = m.group(1)
        brace_open = text.find('{', m.end()-1)
        if brace_open == -1:
            # shouldn't happen
            out.append(text[pos:])
            break
        # find matching closing brace
        i = brace_open + 1
        depth = 1
        L = len(text)
        while i < L and depth > 0:
            c = text[i]
            if c == '{':
                depth += 1
            elif c == '}':
                depth -= 1
            i += 1
        if depth != 0:
            raise RuntimeError('Unmatched braces for struct %s' % name)
        brace_close = i  # index after the closing '}'
        # consume whitespace and optional semicolon
        j = brace_close
        while j < L and text[j].isspace():
            j += 1
        if j < L and text[j] == ';':
            j += 1
        # If this struct is already part of a typedef (e.g. "typedef struct s_name {"),
        # skip converting it to avoid producing "typedef typedef ..." on re-run.
        last_td = text.rfind('typedef', 0, start)
        if last_td != -1:
            # if there's no terminating ';' between that typedef and the struct,
            # assume the struct is already typedef'd and skip conversion.
            if ';' not in text[last_td:start]:
                out.append(text[pos:brace_close])
                pos = j
                continue

        # append text before struct
        out.append(text[pos:start])
        struct_body = text[brace_open:brace_close]  # includes braces
        typedef_name = 't_' + name[2:] if name.startswith('s_') else 't_' + name
        # build replacement: typedef struct NAME { ... } t_NAME;
        replacement = 'typedef struct %s%s %s;' % (name, struct_body, typedef_name)
        # keep a newline after the typedef if original had newlines
        # ensure replacement ends with a single newline
        if not replacement.endswith('\n'):
            replacement += '\n'
        out.append(replacement)
        pos = j
    return ''.join(out)


def main():
    if len(sys.argv) != 2:
        print('Usage: convert_structs.py path/to/header.h')
        sys.exit(2)
    path = sys.argv[1]
    with open(path, 'r', encoding='utf-8') as f:
        text = f.read()
    new_text = convert_structs(text)
    if new_text == text:
        print('No changes')
        return
    backup = path + '.bak'
    with open(backup, 'w', encoding='utf-8') as f:
        f.write(text)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(new_text)
    print('Converted structs in', path)
    print('Backup saved to', backup)

if __name__ == '__main__':
    main()
