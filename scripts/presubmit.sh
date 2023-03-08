#!/usr/bin/env bash

readonly R="======================================="
readonly BOLD="\\033[1m"
readonly ERR="\\033[31;1m"
readonly NORMAL="\\033[0m"

function run() {
  echo ""
  echo -e "${BOLD}${R}${R}"
  echo "Running: $@"
  echo -e "${R}${R}${NORMAL}"
  $@
  ret="$?"
  if [[ "${ret}" -ne 0 ]]; then
    echo ""
    echo -e "${ERR}>>> Error: returned code ${ret} <<<${NORMAL}"
    exit ${ret}
  fi
}

t0="$(date +%s)"

run bazel build //...
run bazel test //...

run bazel build -c opt //...
run bazel test -c opt //...

t1="$(date +%s)"
echo ""
echo "Succeeded after $((t1 - t0)) secs."
