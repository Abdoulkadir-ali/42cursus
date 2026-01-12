#!/usr/bin/env bash
set -eu

TMPDIR=$(mktemp -d /tmp/minitest.XXXX)
cleanup(){ rm -rf "$TMPDIR"; }
trap cleanup EXIT

MINISHELL_BIN="./minishell"
BASH_BIN="bash"

run_case(){
  name="$1"
  cmd="$2"
  echo "\n=== $name ==="

  # Run bash
  if $BASH_BIN -c "$cmd" > "$TMPDIR/bash_${name}.out" 2> "$TMPDIR/bash_${name}.err"; then
    bash_ec=0
  else
    bash_ec=$?
  fi

  # Run minishell
  if "$MINISHELL_BIN" -c "$cmd" > "$TMPDIR/min_${name}.out" 2> "$TMPDIR/min_${name}.err"; then
    min_ec=0
  else
    min_ec=$?
  fi

  echo "-- bash stdout --"
  sed -n '1,200p' "$TMPDIR/bash_${name}.out" || true
  echo "-- bash stderr --"
  sed -n '1,200p' "$TMPDIR/bash_${name}.err" || true
  echo "bash exit: $bash_ec"

  echo "-- minishell stdout --"
  sed -n '1,200p' "$TMPDIR/min_${name}.out" || true
  echo "-- minishell stderr --"
  sed -n '1,200p' "$TMPDIR/min_${name}.err" || true
  echo "minishell exit: $min_ec"
}

# Run a script-style test: write the content to a temp file and feed it to shells.
run_case_script(){
  name="$1"
  script_content="$2"
  echo "\n=== $name (script) ==="
  script_file="$TMPDIR/${name}.sh"
  printf '%s' "$script_content" > "$script_file"
  chmod +x "$script_file"

  if $BASH_BIN "$script_file" > "$TMPDIR/bash_${name}.out" 2> "$TMPDIR/bash_${name}.err"; then
    bash_ec=0
  else
    bash_ec=$?
  fi

  if "$MINISHELL_BIN" < "$script_file" > "$TMPDIR/min_${name}.out" 2> "$TMPDIR/min_${name}.err"; then
    min_ec=0
  else
    min_ec=$?
  fi

  echo "-- bash stdout --"
  sed -n '1,200p' "$TMPDIR/bash_${name}.out" || true
  echo "-- bash stderr --"
  sed -n '1,200p' "$TMPDIR/bash_${name}.err" || true
  echo "bash exit: $bash_ec"

  echo "-- minishell stdout --"
  sed -n '1,200p' "$TMPDIR/min_${name}.out" || true
  echo "-- minishell stderr --"
  sed -n '1,200p' "$TMPDIR/min_${name}.err" || true
  echo "minishell exit: $min_ec"
}

# Test 1: Dynamic operator
cmd1=$'export T=">>"; $T lol'
run_case "dynamic_operator" "$cmd1"

# Test 2: Heredoc delimiter (cat << "$US"E"R")
cmd2=$'export US=\ncat << "$US"E"R"\nbecause\nwe\nlove\nbash\n$USER\n'
# For heredoc we need to feed the here-doc body; run as script
run_case_script "heredoc_delim" "$cmd2"

# Test 3: Redirect to directory
cmd3=$'>> $HOME'
run_case "redir_dir" "$cmd3"

printf "\nAll tests written to %s\n" "$TMPDIR"
exit 0

run_all_failed(){
  LOGFILE="${1:-log/logs}"
  echo "Parsing failed refs from $LOGFILE"
  refs=$(grep -n $'❌' "$LOGFILE" 2>/dev/null | sed -E "s/.*\s(\/[^:]+:[0-9]+)\s*$/\1/" | sort -u || true)
  if [ -z "$refs" ]; then
    echo "No failed refs found in $LOGFILE"
    return 0
  fi
  i=0
  while IFS= read -r ref; do
    [ -z "$ref" ] && continue
    file=${ref%%:*}
    line=${ref#*:}
    i=$((i+1))
    name="failed_$i"
    echo "\n=== $name -> $file:$line ==="
    if [ ! -f "$file" ]; then
      echo "Source file not found: $file" >&2
      continue
    fi
    # Extract a small surrounding context block from the test file (best-effort)
    start=$(( line > 5 ? line - 5 : 1 ))
    end=$(( line + 15 ))
    script_content=$(sed -n "${start},${end}p" "$file" | sed 's/^/\t/')
    if [ -z "$script_content" ]; then
      echo "Empty extraction for $file:$line" >&2
      continue
    fi
    run_case_script "$name" "$script_content"
  done <<EOF
$refs
EOF
}

if [ "${1:-}" = "--all-failed" ]; then
  run_all_failed "${2:-log/logs}"
  exit 0
fi
