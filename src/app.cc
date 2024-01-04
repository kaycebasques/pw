#include <stdio.h>

#include "pw_log/log.h"

// Maybe?
// https://github.com/fcayci/stm32f4-bare-metal/blob/master/projects/uart/uart.c

int main() {
    while (true) {
        PW_LOG_INFO("Hello, PW_LOG_INFO!");
        printf("Hello, printf!");
    }
    return 0;
}
