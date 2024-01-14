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
bazel build --config=stm32 //... --copt="-Wno-error" --platforms=//targets:stm32
```

## Flash

```
bazel run --config=stm32 //tools:flash --copt="-Wno-error"
```

## Communicate

```
bazel run //tools:miniterm -- /dev/ttyACM0 --filter=debug
```

## Resources

* https://www.st.com/en/evaluation-tools/32f429idiscovery.html
* https://github.com/STMicroelectronics/STM32CubeF4/tree/master/Projects/STM32F429I-Discovery
* https://github.com/STMicroelectronics/STM32CubeF4/blob/5983d9348e9b0c230cbe9cd2170159675f8753c6/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery.c
* https://www.st.com/en/embedded-software/stm32cubef4.html#documentation
* https://microcontrollerslab.com/led-blinking-tutorial-stm32f4-discovery-board-gpio-hal-library/
  * It was GPIOG in my case, not GPIOD, but the first blinky did work besides that
