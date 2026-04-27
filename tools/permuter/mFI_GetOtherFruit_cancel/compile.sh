#!/usr/bin/env bash
# Permuter driver: mwcceppc on the candidate .c (args: in.c -o out.o)
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../../.." && pwd)"
cd "$ROOT"
IN="$(realpath "$1")"
OUT="$(realpath "$3")"
exec "$ROOT/build/tools/sjiswrap.exe" "$ROOT/build/compilers/GC/1.3.2/mwcceppc.exe" \
  -nodefaults -proc gekko -align powerpc -enum int -multibyte \
  -char unsigned -fp hardware -Cpp_exceptions off -pragma "cats off" \
  -pragma "warn_notinlined off" -maxerrors 1 -nosyspath \
  -i include -i include/dolphin -i include/libc -i build/GAEJ01_00/include \
  -DVERSION=0 -DNDEBUG=1 -d _LANGUAGE_C -d F3DEX_GBI_2 -d MUST_MATCH \
  -O4,s -inline off -sdata 0 -sdata2 0 -requireprotos -sym on -lang=c \
  -c "$IN" -o "$OUT"
