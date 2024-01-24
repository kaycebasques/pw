// Copyright 2023 The Pigweed Authors
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may not
// use this file except in compliance with the License. You may obtain a copy of
// the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations under
// the License.

#include <cstddef>
#include <string_view>

#include "pw_sys_io/sys_io.h"
#include "pw_function/function.h"

void a_impl(void) {
    const std::string_view message = "handling a...";
    pw::sys_io::WriteLine(message).IgnoreError();
}

pw::Function<void(void)> a_callback(a_impl);

int main() {
    std::byte data;
    while (true) {
        pw::sys_io::ReadByte(&data).IgnoreError();
        switch (data) {
            case static_cast<std::byte>('a'):
                a_callback();
                // Will crash on the second invocation because the callback is
                // assigned to a null pointer here.
                a_callback = nullptr;
                break;
        }
    }
    return 0;
}
