#include <stdint.h>

#include "pw_chrono/system_clock.h"
#include "pw_chrono/system_timer.h"
#include "pw_log/log.h"
#include "pw_system/work_queue.h"

// Define memory-mapped registers for UART
volatile uint32_t* const USART2_SR   = (uint32_t*)0x40004400;
volatile uint32_t* const USART2_DR   = (uint32_t*)0x40004404;
volatile uint32_t* const USART2_BRR  = (uint32_t*)0x40004408;
volatile uint32_t* const USART2_CR1  = (uint32_t*)0x4000440C;

void uart_init() {
    // Configure baud rate and enable UART
    *USART2_BRR = 115200; // Set appropriate baud rate value
    *USART2_CR1 |= (1 << 13); // Enable UART
}

void uart_send_char(char c) {
    while (!(*USART2_SR & (1 << 7))); // Wait for TX empty
    *USART2_DR = c;
}

void uart_send_string(const char* str) {
    while (*str) {
        uart_send_char(*str++);
    }
}

namespace pw::system {
    // This will run once after pw::system::Init() completes. This callback must
    // return or it will block the work queue.
    void UserAppInit() {
        uart_init();
        for (int i = 0; i < 100; i++) {
            uart_send_string("Hello, uart_send_string!\n");
            PW_LOG_INFO("Hello, PW_LOG_INFO!");
            for (int j = 0; j < 1000000; j++) {
                // Wait...
            }
        }
    }
}  // namespace pw::system

// int main() {
//     while (true) {
//         PW_LOG_INFO("Hello, PW_LOG_INFO!");
//         printf("Hello, printf!");
//         for (int i = 0; i < 1000000; i++) {
//             // Wait...
//         }
//     }
//     return 0;
// }
