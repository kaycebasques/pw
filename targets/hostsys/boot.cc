#define PW_LOG_MODULE_NAME "SYS"

#include <chrono>

#include "pw_log/log.h"
#include "pw_system/init.h"
#include "pw_thread/sleep.h"

extern "C" int main() {
  PW_LOG_INFO("Hello, hostsys!");
  pw::system::Init();
  // Sleep loop rather than return on this thread so the process isn't closed.
  while (true) {
    pw::this_thread::sleep_for(std::chrono::seconds(10));
    // It's hard to tell that simulator is alive and working since nothing is
    // logging after initial "boot," so for now log a line occasionally so
    // users can see that the simulator is alive and well.
    PW_LOG_INFO("hello from boot.cc");
    // TODO(amontanez): This thread should probably have a way to exit.
  }
}
