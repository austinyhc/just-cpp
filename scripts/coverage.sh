#!/usr/bin/env bash

if ! which genhtml >/dev/null; then
  echo "Install lcov to get the genhtml program."
  exit 1
fi

set -e
OUTDIR=bazel-coverage

bazel --output_base=/tmp/bazel_output coverage --combined_report=lcov //:all --javabase=@bazel_tools//tools/jdk:remote_jdk11
genhtml --show-details --legend --output-directory $OUTDIR \
  $(find bazel-out/ -name coverage.dat)
ls -l $OUTDIR/index.html
