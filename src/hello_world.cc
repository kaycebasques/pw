#include "pw_log/log.h"

namespace pw::system {
    void UserAppInit() {
        for (int i = 0; i < 100; i++) {
            PW_LOG_INFO("Hello, world!");
            for (int j = 0; j < 1000000; j++) {
                // Spin...
            }
        }
    }
}