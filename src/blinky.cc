#include <cstddef>
#include <cinttypes>

#include "pw_sys_io/sys_io.h"
#include "pw_preprocessor/compiler.h"

#include "stm32f4xx.h"

// Base address for everything peripheral-related on the STM32F4xx.
constexpr uint32_t kPeripheralBaseAddr = 0x40000000u;
// Base address for everything AHB1-related on the STM32F4xx.
constexpr uint32_t kAhb1PeripheralBase = kPeripheralBaseAddr + 0x00020000U;
// Base address for everything APB2-related on the STM32F4xx.
// constexpr uint32_t kApb2PeripheralBase = kPeripheralBaseAddr + 0x00010000U;

// Reset/clock configuration block (RCC).
// `reserved` fields are unimplemented features, and are present to ensure
// proper alignment of registers that are in use.
PW_PACKED(struct) RccBlock {
  uint32_t reserved1[12];
  uint32_t ahb1_config;
  uint32_t reserved2[4];
  uint32_t apb2_config;
};

// GPIO register block definition.
PW_PACKED(struct) GpioBlock {
  uint32_t modes;
  uint32_t out_type;
  uint32_t out_speed;
  uint32_t pull_up_down;
  uint32_t input_data;
  uint32_t output_data;
  uint32_t gpio_bit_set;
  uint32_t port_config_lock;
  uint32_t alt_low;
  uint32_t alt_high;
};

// Constants related to GPIO mode register masks.
constexpr uint32_t kGpioPortModeMask = 0x3u;
constexpr uint32_t kGpio13PortModePos = 26;
constexpr uint32_t kGpioPortModeOutput = 1;

// Constants related to GPIO output mode register masks.
constexpr uint32_t kGpioOutputModeMask = 0x1u;
constexpr uint32_t kGpio13OutputModePos = 13;
constexpr uint32_t kGpioOutputModePushPull = 0;

constexpr uint32_t kGpio13BitSetHigh = 0x1u << 13;
constexpr uint32_t kGpio13BitSetLow = kGpio13BitSetHigh << 16;

// Mask for ahb1_config (AHB1ENR) to enable the "G" GPIO pins.
constexpr uint32_t kGpioGEnable = 0x1u << 6;

// Declare a reference to the memory mapped RCC block.
volatile RccBlock& platform_rcc =
    *reinterpret_cast<volatile RccBlock*>(kAhb1PeripheralBase + 0x3800U);

// Declare a reference to the 'G' GPIO memory mapped block.
volatile GpioBlock& gpio_g =
    *reinterpret_cast<volatile GpioBlock*>(kAhb1PeripheralBase + 0x1800U);

void Init() {
  // Enable 'G' GIPO clocks.
  platform_rcc.ahb1_config |= kGpioGEnable;

  // Enable Pin 13 in output mode.
  gpio_g.modes = (gpio_g.modes & ~(kGpioPortModeMask << kGpio13PortModePos)) |
                 (kGpioPortModeOutput << kGpio13PortModePos);

  // Enable Pin 13 in output mode "push pull"
  gpio_g.out_type =
      (gpio_g.out_type & ~(kGpioOutputModeMask << kGpio13OutputModePos)) |
      (kGpioOutputModePushPull << kGpio13OutputModePos);
}

void TurnOff() { gpio_g.gpio_bit_set = kGpio13BitSetLow; }

void TurnOn() { gpio_g.gpio_bit_set = kGpio13BitSetHigh; }

extern "C" void SystemClock_Config() {
  RCC_OscInitTypeDef RCC_OscInitStruct = {};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
    // pw_boot_PostMain();
  }

  // OverDrive required for operation > 168Mhz
  if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
    // pw_boot_PostMain();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
    // pw_boot_PostMain();
  }
}

void MyInit() {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable the clock of port D of the GPIO
    GPIOD->MODER |= GPIO_MODER_MODER12_0; // Green LED, set pin 12 as output
    GPIOD->MODER |= GPIO_MODER_MODER13_0; // Orange LED, set pin 13 as output
    GPIOD->MODER |= GPIO_MODER_MODER14_0; // Red LED, set pin 14 as output
    GPIOD->MODER |= GPIO_MODER_MODER15_0; // Blue LED, set pin 15 as output
}

/*

https://learnembeddedsystems.co.uk/stm32f4-discovery-beginners-tutorial-blink-leds
https://github.com/aholzbaur/rust-stm32f4-disco-blinky?tab=readme-ov-file
https://github.com/adamgreig/stm32f4-demo
https://github.com/AdrianHuang/stm32f429-led/blob/master/01-SimpleLinkerScript/blink.c

*/

int main() {
    HAL_Init();
    // SystemInit();
    // HAL_Init();
    // SystemClock_Config();
    // Init();
    // HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
    // MyInit();
    // GPIOD->BSRR = 1<<12; // Set the BSRR bit X to 1 to turn respective LED on
    // GPIOD->BSRR = 1<<13; // Set the BSRR bit X to 1 to turn respective LED on
    // GPIOD->BSRR = 1<<14; // Set the BSRR bit X to 1 to turn respective LED on
    // GPIOD->BSRR = 1<<15; // Set the BSRR bit X to 1 to turn respective LED on
    // TurnOn();
    while (true) {}
    return 0;
}
