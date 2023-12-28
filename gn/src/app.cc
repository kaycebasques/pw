#include <unistd.h>

#include "pw_log/log.h"

int main() {
    while (true) {
        PW_LOG_INFO("Hello, world!");
	sleep(3);
    }
    return 0;
}
