#include <cstddef>
#include <cinttypes>

#include "stm32f4xx.h"

void Init_OnBoard_LEDs(void) {
    __HAL_RCC_GPIOG_CLK_ENABLE();
    GPIO_InitTypeDef BoardLEDs;
    BoardLEDs.Mode = GPIO_MODE_OUTPUT_PP;
    BoardLEDs.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    HAL_GPIO_Init(GPIOG, &BoardLEDs);
}

int main() {
    HAL_Init();
    Init_OnBoard_LEDs();
    while (true) {
        // Not sure why LEDs do not appear to toggle on / off
        HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
        for (int i = 0; i < 10000000; i++) {}
    }
    return 0;
}
