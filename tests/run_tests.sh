#!/usr/bin/env bash
# ---------------------------------------------------------------------------
# cub3D tester — run from the repo root:   make test   or   ./tests/run_tests.sh
#
#   ./tests/run_tests.sh            parsing tests (invalid maps + arguments)
#   ./tests/run_tests.sh --valid    + valid maps (opens a window ~2s each)
#   ./tests/run_tests.sh --leaks    + valgrind on every error case (Linux)
#
# Invalid map  -> must exit != 0, first line of output must be "Error"
# Valid map    -> must still be running after TIMEOUT seconds (no crash,
#                 no "Error"). Needs a display (xvfb-run in the CI).
# ---------------------------------------------------------------------------

BIN=./cub3D
TIMEOUT=2
RUN_VALID=0
RUN_LEAKS=0
PASS=0
FAIL=0
VG_LOG=$(mktemp)
trap 'rm -f "$VG_LOG"' EXIT

GREEN="\033[32m"; RED="\033[31m"; YELLOW="\033[33m"; RESET="\033[0m"

for arg in "$@"; do
	case "$arg" in
		--valid) RUN_VALID=1 ;;
		--leaks) RUN_LEAKS=1 ;;
	esac
done

if [ ! -x "$BIN" ]; then
	echo "cub3D not found, run make first"; exit 1
fi

# run_limited <seconds> <cmd...> : runs cmd, kills it after <seconds>.
# Exit code 142 = killed by the timer (= still running = OK for valid maps).
run_limited() {
	local secs=$1; shift
	perl -e 'alarm shift; exec @ARGV' "$secs" "$@"
}

ok()   { PASS=$((PASS + 1)); printf "${GREEN}[OK]${RESET}   %s\n" "$1"; }
ko()   { FAIL=$((FAIL + 1)); printf "${RED}[KO]${RESET}   %s  -> %s\n" "$1" "$2"; }

# expect_error <description> <args...>
expect_error() {
	local desc=$1; shift
	local out code first
	out=$(run_limited 5 "$BIN" "$@" 2>&1); code=$?
	first=$(printf "%s\n" "$out" | head -n 1)
	if [ $code -eq 0 ]; then
		ko "$desc" "exit code 0, expected an error"
	elif [ $code -ge 128 ]; then
		ko "$desc" "crash or timeout (exit $code)"
	elif [ "$first" != "Error" ]; then
		ko "$desc" "first line is '$first', expected 'Error'"
	else
		ok "$desc"
	fi
	if [ $RUN_LEAKS -eq 1 ]; then
		expect_no_leak "$desc" "$@"
	fi
}

expect_no_leak() {
	local desc=$1; shift
	if ! command -v valgrind >/dev/null; then
		printf "${YELLOW}[SKIP]${RESET} valgrind not installed\n"; return
	fi
	valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all \
		--error-exitcode=42 -q "$BIN" "$@" >/dev/null 2>"$VG_LOG"
	if [ $? -eq 42 ]; then
		ko "leaks: $desc" "see valgrind output below"; cat "$VG_LOG"
	else
		ok "leaks: $desc"
	fi
}

# expect_running <map> : valid map, the program must not stop by itself
expect_running() {
	local map=$1 out code
	out=$(run_limited $TIMEOUT "$BIN" "$map" 2>&1); code=$?
	if [ $code -eq 142 ] && ! printf "%s" "$out" | grep -q "^Error"; then
		ok "valid: $map"
	else
		ko "valid: $map" "stopped with exit $code: $(printf "%s" "$out" | head -n 2 | tr '\n' ' ')"
	fi
}

echo "=== Arguments ==="
expect_error "no argument"
expect_error "two arguments" maps/valid/minimal.cub maps/valid/minimal.cub
expect_error "file does not exist" maps/does_not_exist.cub
expect_error "wrong extension (.ber)" maps/invalid/wrong_extension.ber
expect_error "directory named .cub" tests/fixtures/folder.cub

echo "=== Invalid maps ==="
for map in maps/invalid/*.cub; do
	expect_error "$map" "$map"
done

if [ $RUN_VALID -eq 1 ]; then
	echo "=== Valid maps ==="
	for map in maps/valid/*.cub; do
		expect_running "$map"
	done
fi

echo
printf "Result: ${GREEN}%d passed${RESET}, ${RED}%d failed${RESET}\n" "$PASS" "$FAIL"
[ $FAIL -eq 0 ]
