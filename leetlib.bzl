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


def exists(path):
    found = native.glob([path])
    return len(found) > 0

def leetlib_gen():

    tests = native.glob(["test/*_test.cc"])

    for test in tests:
        test_name = paths.basename(test).split("_test")[0]
        source_path = "src/" + test_name + ".h"

        if not exists(source_path):
            fail("%s does not exist." % source_path)

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

def leetlib_tools():

    native.cc_library(
        name = "nlohmann",
        srcs = ["deps/nlohmann/json.hpp"],
    )

    native.cc_library(
        name = "httplib",
        srcs = ["deps/httplib/httplib.h"],
    )

    native.cc_library(
        name = "cxxopts",
        srcs = ["deps/cxxopts/cxxopts.hpp"],
    )

    native.cc_binary(
        name = "leetlib",
        srcs = ["tools/leetlib.cpp"],
        deps = [
            ":nlohmann",
            ":httplib",
            ":cxxopts"
        ]
    )
