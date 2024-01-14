#include <cstddef>
#include <cinttypes>

#include "stm32f4xx.h"

void Init_OnBoard_LEDs(void)
{
	 __HAL_RCC_GPIOG_CLK_ENABLE();
	GPIO_InitTypeDef BoardLEDs;
	BoardLEDs.Mode = GPIO_MODE_OUTPUT_PP;
	BoardLEDs.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	HAL_GPIO_Init(GPIOG, &BoardLEDs);
}

int main() {
    HAL_Init();
    Init_OnBoard_LEDs();
    HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    while (true) {
        // HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
    }
    return 0;
}
