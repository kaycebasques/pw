# Pigweed: minimal Bazel example

This repository contains a minimal example of a Bazel-based Pigweed project.
It's an echo application for the STM32F429 Discovery Board.

## Cloning

```
git clone --recursive https://pigweed.googlesource.com/example/echo
```

If you already cloned but forgot to include `--recursive`, run `git submodule
update --init` to pull all submodules.

TODO: b/300695111 - Don't require submodules for this example.

## Building

We'll assume you already have Bazel on your system. If you don't, the
recommended way to get it is through
[Bazelisk](https://github.com/bazelbuild/bazelisk/blob/master/README.md).

To build the entire project (including building the application for both the
host and the STM32 Discovery Board), run

```
bazel build //...
```

To run the application locally on your machine, run,

```
bazel run //src:echo
```

## Flashing

To flash the firmware to a STM32F429 Discovery Board connected to your machine,
run,

```
bazel run //tools:flash
```

Note that you _don't need to build the firmware first_: Bazel knows that the
firmware images are needed to flash the board, and will build them for you. And
if you edit the source of the firmware or any of its dependencies, it will get
rebuilt when you flash.

## Communicating

Run,

```
bazel run //tools:miniterm -- /dev/ttyACM0 --filter=debug
```

to communicate with the board. When you transmit a character, you should get
the same character back!
