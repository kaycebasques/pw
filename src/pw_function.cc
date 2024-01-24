#include <string_view>

#include "pw_function/function.h"
#include "pw_sys_io/sys_io.h"

// pw::Function can be constructed from a function pointer. pw::Function
// implements the call operator; invoking the pw::Function object forwards to
// the stored callable.
int _a(int a, int b) { return a + b; }
pw::Function<int(int, int)> add(_a);

// pw::Function can be constructed from a lambda.
pw::Function<int(int)> square([](int num) { return num * num; });

// pw::Callback can only be invoked once. After the first call, the target
// function is released and destructed, along with any resources owned by that
// function.
pw::Callback<void(void)> flip_table_once([](void) {
  std::string_view message = (std::string_view) "(╯°□°)╯︵ ┻━┻";
  pw::sys_io::WriteLine(message);
});

// pw:Function can be used in place of function pointers to improve signature
// readability.
//
// Before:
// void handle_event(int data, void (*callback)(int result));
//
// After:
// void handle_event(int data, const pw::Function<void(int result)>& callback);

int main() {
  while (true) {
    add(5, 6);
    // pw::Function is nullable. Invoking a null function triggers a runtime
    // assert.
    add = nullptr;
    square(4);
    flip_table_once();
  }
  return 0;
}
