# pwbzl

Pigweed apps in a Bazel-based project.

Forked from <https://pigweed.googlesource.com/example/echo>.

## Install

```
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.39.7/install.sh | bash
nvm install --lts
nvm use --lts
npm install -g @bazel/bazelisk
git clone --recursive git@github.com:kaycebasques/pwbzl.git
```

## Build

```
bazel build //...
```

## Flash

```
bazel run //tools:flash
```

## Communicate

```
bazel run //tools:miniterm -- /dev/ttyACM0 --filter=debug
```
