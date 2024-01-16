#include <cstddef>
#include <cinttypes>

#include "pw_sys_io/sys_io.h"
#include "stm32f4xx.h"

// https://cs.opensource.google/pigweed/pigweed/+/9ad961bb7bbd3767c4b0798f2c9553413fc962a2:targets/stm32f429i_disc1_stm32cube/boot.cc;l=46
// void SystemClock_Config() {
//   RCC_OscInitTypeDef RCC_OscInitStruct = {};
//   RCC_ClkInitTypeDef RCC_ClkInitStruct = {};
//   __HAL_RCC_PWR_CLK_ENABLE();
//   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//   RCC_OscInitStruct.PLL.PLLM = 4;
//   RCC_OscInitStruct.PLL.PLLN = 180;
//   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//   RCC_OscInitStruct.PLL.PLLQ = 8;
//   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
//     // pw_boot_PostMain();
//   }
//   // OverDrive required for operation > 168Mhz
//   if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
//     // pw_boot_PostMain();
//   }
//   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
//                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
//   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
//   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
//   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
//     // pw_boot_PostMain();
//   }
// }

// void Init_OnBoard_LEDs(void) {
//     __HAL_RCC_GPIOG_CLK_ENABLE();
//     GPIO_InitTypeDef BoardLEDs;
//     BoardLEDs.Mode = GPIO_MODE_OUTPUT_PP;
//     // BoardLEDs.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//     BoardLEDs.Pin = GPIO_PIN_14;
//     HAL_GPIO_Init(GPIOG, &BoardLEDs);
// }

// void UART_Init() {
//   GPIO_InitTypeDef GPIO_InitStruct = {};
// 
//   USART_ENABLE();
//   USART_GPIO_TX_PORT_ENABLE();
//   USART_GPIO_RX_PORT_ENABLE();
// 
//   GPIO_InitStruct.Pin = USART_GPIO_TX_PIN;
//   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   GPIO_InitStruct.Alternate = USART_GPIO_ALTERNATE_FUNC;
//   HAL_GPIO_Init(USART_GPIO_TX_PORT, &GPIO_InitStruct);
// 
//   GPIO_InitStruct.Pin = USART_GPIO_RX_PIN;
//   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
//   GPIO_InitStruct.Pull = GPIO_NOPULL;
//   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//   GPIO_InitStruct.Alternate = USART_GPIO_ALTERNATE_FUNC;
//   HAL_GPIO_Init(USART_GPIO_RX_PORT, &GPIO_InitStruct);
// 
//   uart.Instance = USART_INSTANCE;
//   uart.Init.BaudRate = 115200;
//   uart.Init.WordLength = UART_WORDLENGTH_8B;
//   uart.Init.StopBits = UART_STOPBITS_1;
//   uart.Init.Parity = UART_PARITY_NONE;
//   uart.Init.Mode = UART_MODE_TX_RX;
//   uart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//   uart.Init.OverSampling = UART_OVERSAMPLING_16;
//   HAL_UART_Init(&uart);
// }

int main() {
  // HAL_Init();
  while (true) {
    std::byte data;
    pw::sys_io::ReadByte(&data).IgnoreError();
    std::byte mychar = (std::byte) '!';
    pw::sys_io::WriteByte(mychar).IgnoreError();
  }
  return 0;
}

// int main() {
//     SystemInit();
//     HAL_Init();
//     // SystemClock_Config();
//     Init_OnBoard_LEDs();
//     while (true) {
//         // Not sure why LEDs do not appear to toggle on / off
//         HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
//         HAL_Delay(1000);
//         // for (int i = 0; i < 10000000; i++) {}
//     }
//     return 0;
// }
