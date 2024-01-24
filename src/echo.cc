#include <cstddef>

#include "pw_sys_io/sys_io.h"

int main() {
  while (true) {
    std::byte data;
    pw::sys_io::ReadByte(&data).IgnoreError();
    pw::sys_io::WriteByte(data).IgnoreError();
  }
  return 0;
}
