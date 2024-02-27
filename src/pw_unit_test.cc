#include "pw_unit_test_lib.h"

#include "pw_unit_test/framework.h"

namespace {

TEST(MyTestSuite, MyTestCase) {
  pw::InlineString<32> expected = "(╯°□°)╯︵ ┻━┻";
  pw::InlineString<32> actual = app::flip_table();
  EXPECT_STREQ(actual.c_str(), expected.c_str());
}

}
