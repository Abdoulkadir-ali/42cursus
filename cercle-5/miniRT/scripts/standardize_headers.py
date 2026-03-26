#!/usr/bin/env python3
"""
Standardize C header files in `includes/`.

Ordering enforced inside header guard (between `#define` and `#endif`):
1. External imports (`#include <...>`)
2. Module imports (`#include "..."`)
3. `#define` macros
4. `typedef enum` blocks
5. `typedef struct` blocks
6. Function prototypes grouped by return type (groups sorted by return type, names alphabetical), blank line between return-type groups

Usage:
  python3 scripts/standardize_headers.py --dry-run    # print proposed changes
  python3 scripts/standardize_headers.py --apply      # overwrite files (creates .bak)

This is conservative: it preserves top comment blocks and header guards.
"""
import argparse
import os
import re
import shutil
import tempfile
from collections import defaultdict


INCLUDES_DIR = os.path.join(os.path.dirname(__file__), '..', 'includes')


def read_file(path):
    with open(path, 'r', encoding='utf-8') as f:
        return f.read()


def write_file_atomic(path, content):
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(path))
    with os.fdopen(fd, 'w', encoding='utf-8') as f:
        f.write(content)
    shutil.move(tmp, path)


INC_RE = re.compile(r'^\s*#\s*include\s*(<[^>]+>|"[^"]+")')
DEFINE_RE = re.compile(r'^\s*#\s*define\b')
TYPEDEF_ENUM_RE = re.compile(r'\btypedef\s+enum\b')
TYPEDEF_STRUCT_RE = re.compile(r'\btypedef\s+struct\b')
FUNC_SIG_RE = re.compile(r'^(?P<ret>[^;\(\)]+?)\s+(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*\(')


def split_header(content):
    # preserve leading comment block (/* ... */) if present
    header_comment = ''
    rest = content
    m = re.match(r'^(\s*/\*.*?\*/\s*)', content, re.DOTALL)
    if m:
        header_comment = m.group(1)
        rest = content[m.end():]

    # find header guard
    guard_start = re.search(r'^\s*#\s*ifndef\b.*$', rest, re.MULTILINE)
    if not guard_start:
        # no guard: operate on whole file
        return header_comment, None, rest, None
    define_line = re.search(r'^\s*#\s*define\b.*$', rest[guard_start.end():], re.MULTILINE)
    if not define_line:
        return header_comment, None, rest, None
    define_pos = guard_start.end() + define_line.start()
    # find last #endif
    endif_match = None
    for m in re.finditer(r'^\s*#\s*endif\b.*$', rest, re.MULTILINE):
        endif_match = m
    if not endif_match:
        return header_comment, None, rest, None

    pre = rest[:define_pos + (rest[define_pos:].find('\n') + 1)]
    inner = rest[pre.__len__():endif_match.start()]
    post = rest[endif_match.start():]
    return header_comment, pre, inner, post


def collect_blocks(inner):
    lines = inner.splitlines(keepends=True)
    i = 0
    external_includes = []
    module_includes = []
    defines = []
    typedef_enums = []
    typedef_structs = []
    functions = []
    others = []

    def gather_until_semicolon(start):
        buf = ''
        j = start
        while j < len(lines):
            buf += lines[j]
            if ';' in lines[j]:
                return buf, j + 1
            j += 1
        return buf, j

    while i < len(lines):
        line = lines[i]
        if INC_RE.match(line):
            inc = line.strip()
            if inc.find('<') != -1:
                external_includes.append(inc)
            else:
                module_includes.append(inc)
            i += 1
            continue
        if DEFINE_RE.match(line):
            # collect macro block (handle backslash continuation)
            buf = line
            i += 1
            while buf.rstrip().endswith('\\') and i < len(lines):
                buf += lines[i]
                i += 1
            defines.append(buf)
            continue
        tail = ''.join(lines[i:i+5])  # small lookahead
        if TYPEDEF_ENUM_RE.search(tail):
            block, ni = gather_until_semicolon(i)
            typedef_enums.append(block)
            i = ni
            continue
        if TYPEDEF_STRUCT_RE.search(tail):
            block, ni = gather_until_semicolon(i)
            typedef_structs.append(block)
            i = ni
            continue
        # function prototype: detect '(' before ';' on possibly multi-line
        if '(' in line:
            buf, ni = gather_until_semicolon(i)
            if '(' in buf and ')' in buf and ';' in buf:
                # probable prototype
                functions.append(buf)
                i = ni
                continue
        # otherwise, collect as other
        others.append(line)
        i += 1

    return (external_includes, module_includes, defines,
            typedef_enums, typedef_structs, functions, others)


def extract_alias(block):
    # try to find trailing alias after '}' e.g. '} t_name;' or '} t_name ;'
    m = re.search(r'}\s*([A-Za-z_][A-Za-z0-9_]*)\s*;', block)
    if m:
        return m.group(1)
    # fallback: try last word before semicolon
    m2 = re.search(r'([A-Za-z_][A-Za-z0-9_]*)\s*;\s*$', block)
    return m2.group(1) if m2 else ''


def normalize_whitespace(s):
    return re.sub(r'\s+', ' ', s).strip()


def group_and_sort_functions(funcs):
    groups = defaultdict(list)
    for f in funcs:
        one = re.sub(r'\s+', ' ', f.replace('\n', ' ')).strip()
        m = FUNC_SIG_RE.match(one)
        if m:
            ret = normalize_whitespace(m.group('ret'))
            name = m.group('name')
            groups[ret].append((name, f))
        else:
            groups[''].append(('', f))
    # sort groups by return type
    out = []
    for ret in sorted(groups.keys()):
        items = sorted(groups[ret], key=lambda x: x[0])
        out.append((ret, [it[1] for it in items]))
    return out


def build_new_inner(external_includes, module_includes, defines,
                    typedef_enums, typedef_structs, functions, others):
    pieces = []
    if external_includes:
        for inc in sorted(set(external_includes)):
            pieces.append(inc + '\n')
        pieces.append('\n')
    if module_includes:
        for inc in sorted(set(module_includes)):
            pieces.append(inc + '\n')
        pieces.append('\n')
    if defines:
        for d in defines:
            pieces.append(d if d.endswith('\n') else d + '\n')
        pieces.append('\n')
    if typedef_enums:
        # sort by alias
        keyed = sorted(typedef_enums, key=lambda b: extract_alias(b))
        for b in keyed:
            pieces.append(b if b.endswith('\n') else b + '\n')
        pieces.append('\n')
    if typedef_structs:
        keyed = sorted(typedef_structs, key=lambda b: extract_alias(b))
        for b in keyed:
            pieces.append(b if b.endswith('\n') else b + '\n')
        pieces.append('\n')
    if functions:
        grouped = group_and_sort_functions(functions)
        for ret, flist in grouped:
            for f in flist:
                pieces.append(f if f.endswith('\n') else f + '\n')
            pieces.append('\n')
    # append others (trim leading/trailing whitespace)
    if others:
        pieces.append(''.join(others))
    return ''.join(pieces)


def process_file(path, apply=False):
    orig = read_file(path)
    header_comment, pre, inner, post = split_header(orig)
    if pre is None:
        # no guard — operate on whole file conservatively: only reorder includes
        content = orig
        header_comment = ''
        pre = ''
        inner = orig
        post = ''

    (external_includes, module_includes, defines,
     typedef_enums, typedef_structs, functions, others) = collect_blocks(inner)

    new_inner = build_new_inner(external_includes, module_includes, defines,
                                typedef_enums, typedef_structs, functions, others)

    new_content = header_comment + pre + new_inner + post
    if normalize_whitespace(new_content) == normalize_whitespace(orig):
        return False, None

    if apply:
        bak = path + '.bak'
        if not os.path.exists(bak):
            shutil.copy2(path, bak)
        write_file_atomic(path, new_content)
        return True, bak
    else:
        return True, new_content


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--apply', action='store_true', help='Apply changes (creates .bak)')
    ap.add_argument('--dir', default=INCLUDES_DIR, help='Headers directory')
    args = ap.parse_args()

    changed = []
    for fn in sorted(os.listdir(args.dir)):
        if not fn.endswith('.h'):
            continue
        path = os.path.join(args.dir, fn)
        ok, res = process_file(path, apply=args.apply)
        if ok:
            changed.append((path, res))

    if not changed:
        print('No changes necessary.')
        return 0

    if args.apply:
        print('Applied changes to:')
        for p, bak in changed:
            print(' -', p, '(backup at', bak + ')')
    else:
        print('Proposed changes for:')
        for p, new in changed:
            print('---', p, '---')
            print(new)
            print('--- end ---\n')

    return 0


if __name__ == '__main__':
    raise SystemExit(main())
