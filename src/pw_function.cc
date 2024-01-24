#include <cstddef>
#include <string_view>

#include "pw_sys_io/sys_io.h"
#include "pw_function/function.h"

// void handle_user_command(int arg, void (*callback)(int result));

// Return an int and do stuff based on the retval
int _impl(std::byte command) {
    std::byte response;
    switch (command) {
        case static_cast<std::byte>('a'):
            response = (std::byte) 'a';
            pw::sys_io::WriteByte(response).IgnoreError();
            return 0;
        case static_cast<std::byte>('x'):
            response = (std::byte) '!';
            pw::sys_io::WriteByte(response).IgnoreError();
            return 1;
    }
    return 0;
}

const pw::Function<int(std::byte)> callback(_impl);

// void handle_user_command(int arg, void (*callback)(int result));
void handle_user_command(std::byte command, const pw::Function<int(std::byte)>& callback) {
    int result = callback(command);
    if (result) {
        // Do something...
    }
}

int main() {
    std::byte data;
    while (true) {
        pw::sys_io::ReadByte(&data).IgnoreError();
        handle_user_command(data, callback);
    }
    return 0;
}
