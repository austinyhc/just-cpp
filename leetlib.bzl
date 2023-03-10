# Copyright 2023 Austin Chen

load("@bazel_skylib//lib:paths.bzl", "paths")

def leetlib_deps():
    native.cc_library(
        name = "base",
        visibility = ["//visibility:public"],
        strip_include_prefix = "utils",
        hdrs = [
            "utils/base.h",
            "utils/tree.h",
            "utils/linked_list.h",
            "utils/nested_integer.h",
        ],
        deps = [
            "@com_github_google_benchmark//:benchmark",
            "@com_google_googletest//:gtest_main",
            "@com_google_absl//absl/strings",
        ],
    )

def leetlib_gen():

    tests = native.glob(["test/*_test.cc"])

    for test in tests:
        test_name = paths.basename(test).split("_test")[0]
        source_path = "src/" + test_name + ".h"

    source_files = native.glob(["src/*.h"], ["src/0000_*"])
    no_test_source_files = []
    for source_file in source_files:
        target_name = source_file[4:-2]
        test_file = "test/" + target_name + "_test.cc"

        native.cc_library(
            name = test_name,
            srcs = [source_path],
            deps = [
                "@com_google_googletest//:gtest_main",
                ":base",
            ],
            visibility = ["//visibility:public"],
        )

        native.cc_test(
            name = test_name + "_test",
            srcs = [test],
            copts = ["-Isrc/"],
            deps = [
                "//:" + test_name,
            ],
        )

