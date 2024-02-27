#include "pw_unit_test_lib.h"

#include "pw_string/string.h"

namespace app {

pw::InlineString<32> flip_table() {
  pw::InlineString<32> textmoji = "(╯°□°)╯︵ ┻━┻";
  return textmoji;
}

}
