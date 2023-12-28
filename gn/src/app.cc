#include "pw_log/log.h"

int main() {
    while (true) {
        PW_LOG_INFO("Hello, PW_LOG_INFO!");
        printf("Hello, printf!");
        for (int i = 0; i < 1000000; i++) {
            // Wait...
        }
    }
    return 0;
}
