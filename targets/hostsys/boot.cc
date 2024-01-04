#define PW_LOG_MODULE_NAME "hostsys"

#include <chrono>

#include "pw_log/log.h"
#include "pw_system/init.h"
#include "pw_thread/sleep.h"

extern "C" int main() {
    PW_LOG_INFO("Booting...");
    pw::system::Init();
    // Process will close if this thread returns.
    while (true) {
        pw::this_thread::sleep_for(std::chrono::seconds(10));
        PW_LOG_INFO("Still alive...");
    }
}
