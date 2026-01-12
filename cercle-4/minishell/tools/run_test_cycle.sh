#!/usr/bin/env bash
# Run the official tester, extract failing cases, and produce reproductions.

ROOT_DIR="$(pwd)"
TESTER="/home/abdali/42_minishell_tester/tester.sh"
OUT_FULL="/tmp/minishell_full_tester_output.txt"
OUT_FAILS="/tmp/minishell_failures.txt"
OUT_FAILED_CASES="/tmp/minishell_failed_cases.txt"
OUT_REPRO="/tmp/minishell_repro.txt"

N=${1:-5}

echo "Building project..."
make re >/dev/null 2>&1 || { echo "make failed"; exit 1; }

echo "Running tester (this may take several minutes)..."
"$TESTER" a 2>&1 | tee "$OUT_FULL"

grep '❌' "$OUT_FULL" > "$OUT_FAILS" || true
awk '{print $NF}' "$OUT_FAILS" | sort | uniq > "$OUT_FAILED_CASES" || true

rm -f "$OUT_REPRO"
count=0
while IFS= read -r fl; do
  if [ -z "$fl" ]; then
    continue
  fi
  count=$((count+1))
  file=${fl%:*}
  line=${fl##*:}
  echo "=== CASE $count: $file:$line ===" >> "$OUT_REPRO"
  sed -n "$((line-2)),$((line+2))p" "$file" >> "$OUT_REPRO" 2>/dev/null || true
  cmd=$(sed -n "${line}p" "$file")
  echo "CMD: $cmd" >> "$OUT_REPRO"
  echo "--- bash output ---" >> "$OUT_REPRO"
  bash -c "$cmd" >> "$OUT_REPRO" 2>&1 || true
  echo "bash rc: $?" >> "$OUT_REPRO"
  echo "--- minishell output ---" >> "$OUT_REPRO"
  printf "%s\n" "$cmd" | "$ROOT_DIR"/minishell >> "$OUT_REPRO" 2>&1 || true
  echo "minishell rc: $?" >> "$OUT_REPRO"
  echo "" >> "$OUT_REPRO"
  if [ $count -ge "$N" ]; then
    break
  fi
done < "$OUT_FAILED_CASES"

echo "Reproductions saved to $OUT_REPRO"
echo "Failures saved to $OUT_FAILS"
echo "Full tester output: $OUT_FULL"

exit 0
