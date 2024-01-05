#define PW_LOG_MODULE_NAME "app"

#include "pw_log/log.h"
#include "pw_string/string_builder.h"

namespace pw::system {
    void UserAppInit() {
        pw::StringBuffer<32> message;
        message << "Hello, world!";
        PW_LOG_INFO("%s", message.c_str());
    }
}
