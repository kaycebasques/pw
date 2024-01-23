# pw

[Pigweed](https://pigweed.dev) + [Bazel](https://bazel.dev)

## Setup

```
git clone --recursive git@github.com:kaycebasques/pw.git
```

## Build

```
bazel build //...
```

## Run

```
bazel run //src:echo
```

## Flash

```
bazel run //tools:flash
```

## Communicate

```
bazel run //tools:miniterm -- /dev/ttyACM0 --filter=debug
```
