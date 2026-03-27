#!/usr/bin/env python3
"""
move_constants_to_header.py

Scan the `includes/` folder for simple `#define NAME value` macros (no function-like macros),
collect them into `includes/constants.h`, remove originals and insert an `#include "constants.h"`
in files where defines were removed.

Usage:
    python3 scripts/move_constants_to_header.py [--includes DIR] [--out FILE] [--no-include] [--dry-run] [--force]

Options:
    --includes DIR   (default: includes)
    --out FILE       (default: includes/constants.h)
    --no-include     Do not insert #include "constants.h" into modified files
    --dry-run        Show what would change without writing files
    --force          Overwrite existing constants with later definitions on conflict

This script creates backups of modified files with a `.bak` suffix.
"""

import os
import re
import argparse
from collections import OrderedDict

DEFINE_RE = re.compile(r'^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.*)\s*$')
FUNC_MACRO_RE = re.compile(r'^\s*#\s*define\s+([A-Za-z_][A-Za-z0-9_]*)\s*\(')


def find_include_files(includes_dir):
    paths = []
    for root, dirs, files in os.walk(includes_dir):
        for f in files:
            if f.endswith('.h') or f.endswith('.hpp') or f.endswith('.inl'):
                paths.append(os.path.join(root, f))
    return paths


def build_constants_header(defines, out_path):
    guard = os.path.basename(out_path).upper().replace('.', '_')
    lines = []
    lines.append('/* Auto-generated constants header */\n')
    lines.append('#ifndef %s\n' % guard)
    lines.append('#define %s\n\n' % guard)
    for name, (value, src) in defines.items():
        lines.append('#define %s %s\n' % (name, value))
    lines.append('\n#endif /* %s */\n' % guard)
    return ''.join(lines)


def remove_defines_from_file(path, names_to_remove, dry_run=False, backup=True, insert_include=True, out_header='includes/constants.h'):
    with open(path, 'r', encoding='utf-8') as fh:
        lines = fh.readlines()
    changed = False
    new_lines = []
    for line in lines:
        m = DEFINE_RE.match(line)
        if m and m.group(1) in names_to_remove and not FUNC_MACRO_RE.match(line):
            changed = True
            continue
        new_lines.append(line)
    if not changed:
        return False
    if insert_include:
        # ensure we include the constants header once near top (after existing includes)
        include_line = '#include "' + os.path.relpath(out_header, os.path.dirname(path)).replace('\\', '/') + '"\n'
        # if include already present, skip inserting
        if include_line not in new_lines:
            # find last include index
            last_inc = -1
            for idx, l in enumerate(new_lines[:50]):
                if l.strip().startswith('#include'):
                    last_inc = idx
            insert_at = last_inc + 1
            new_lines.insert(insert_at, include_line)
    if dry_run:
        print('[DRY RUN] Would modify', path)
        return True
    # backup
    if backup:
        bak = path + '.bak'
        if not os.path.exists(bak):
            os.rename(path, bak)
        else:
            # if backup exists, still proceed but don't overwrite
            os.remove(path)
    with open(path, 'w', encoding='utf-8') as fh:
        fh.writelines(new_lines)
    return True


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--includes', default='includes', help='includes directory to scan')
    p.add_argument('--out', default='includes/constants.h', help='output header path')
    p.add_argument('--no-include', action='store_true', help="Don't insert #include into modified files")
    p.add_argument('--dry-run', action='store_true')
    p.add_argument('--force', action='store_true', help='Allow later definitions to overwrite earlier ones')
    args = p.parse_args()

    includes_dir = args.includes
    out_path = args.out

    files = find_include_files(includes_dir)
    files = [f for f in files if os.path.abspath(f) != os.path.abspath(out_path)]
    print('Scanning', len(files), 'include files...')

    # collect
    defines = OrderedDict()
    # iterate and parse to preserve discovery order
    for path in files:
        with open(path, 'r', encoding='utf-8') as fh:
            lines = fh.readlines()
        for line in lines:
            if FUNC_MACRO_RE.match(line):
                continue
            m = DEFINE_RE.match(line)
            if m:
                name = m.group(1)
                value = m.group(2).rstrip()
                if name in defines and defines[name][0] != value:
                    print('Conflict for', name, 'in', path)
                    if args.force:
                        print(' - overwriting previous definition with this one')
                        defines[name] = (value, path)
                else:
                    if name not in defines:
                        defines[name] = (value, path)
    if not defines:
        print('No simple #define constants found.')
        return

    # build header content
    header_content = build_constants_header(defines, out_path)
    print('Collected', len(defines), 'defines. Writing to', out_path)
    if args.dry_run:
        print(header_content)
    else:
        # ensure directory
        os.makedirs(os.path.dirname(out_path), exist_ok=True)
        if os.path.exists(out_path):
            # backup existing
            os.rename(out_path, out_path + '.bak')
        with open(out_path, 'w', encoding='utf-8') as fh:
            fh.write(header_content)

    # modify files: remove defines and add include
    for path in files:
        # determine which defines were in this file
        names_in_file = []
        with open(path, 'r', encoding='utf-8') as fh:
            lines = fh.readlines()
        for line in lines:
            m = DEFINE_RE.match(line)
            if m and m.group(1) in defines and not FUNC_MACRO_RE.match(line):
                names_in_file.append(m.group(1))
        if names_in_file:
            changed = remove_defines_from_file(path, set(names_in_file), dry_run=args.dry_run, backup=not args.dry_run, insert_include=not args.no_include, out_header=out_path)
            if changed:
                print('Updated', path)

    print('Done.')

if __name__ == '__main__':
    main()
