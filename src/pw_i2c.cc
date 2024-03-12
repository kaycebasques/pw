#include <chrono>

#include "pw_bytes/array.h"
#include "pw_i2c/address.h"
#include "pw_i2c/device.h"
#include "pw_i2c/initiator_mock.h"
#include "pw_log/log.h"
#include "pw_result/result.h"
#include "pw_unit_test/framework.h"

using namespace std::chrono_literals;

namespace {

TEST(I2CTestSuite, I2CWriteTestCase) {
  constexpr pw::i2c::Address kAddress = pw::i2c::Address::SevenBit<0x01>();
  constexpr auto kExpectedWrite = pw::bytes::Array<1, 2, 3>();
  auto expected_transactions = pw::i2c::MakeExpectedTransactionArray(
    {pw::i2c::WriteTransaction(pw::OkStatus(), kAddress, kExpectedWrite, 1ms)}
  );
  pw::i2c::MockInitiator initiator(expected_transactions);
  pw::ConstByteSpan kActualWrite = pw::bytes::Array<1, 2, 3>();
  pw::Status status = initiator.WriteFor(kAddress, kActualWrite, 1ms);
  if (status.ok()) {
    PW_LOG_INFO("OK");
  } else { 
    PW_LOG_INFO("NOT OK");
  }
  // SUCCEED();
  // FAIL();
  EXPECT_EQ(initiator.Finalize(), pw::OkStatus());
}

}
