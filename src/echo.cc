#include <cstddef>

// #// include "pw_sys_io/sys_io.h"
#include "pw_sys_io_stm32cube/init.h"

int main() {
    pw_sys_io_Init();
    while (true) {
        // std::byte data;
        // pw::sys_io::ReadByte(&data).IgnoreError();
        // std::byte mychar = (std::byte) 'c';
        // pw::sys_io::WriteByte(mychar).IgnoreError();
    }
    return 0;
}
