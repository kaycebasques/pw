#define PW_LOG_MODULE_NAME "app"

#include "pw_log/log.h"

namespace pw::system {
    void UserAppInit() {
        PW_LOG_INFO("Hello, world!");
    }
}
