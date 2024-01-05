#define PW_LOG_MODULE_NAME "app"

#include "pw_log/log.h"
#include "pw_string/string_builder.h"
#include "pw_function/function.h"

void print_message() {
    pw::StringBuffer<32> message;
    message << "Hello, world!";
    PW_LOG_INFO("%s", message.c_str());
    return;
}

int main() {
    pw::Function<void()> hello_world(print_message);
    hello_world();
    return 0;
}
