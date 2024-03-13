#include <chrono>

#include "pw_bytes/array.h"
#include "pw_i2c/address.h"
#include "pw_i2c/device.h"
#include "pw_i2c_linux/initiator.h"
#include "pw_log/log.h"
#include "pw_result/result.h"

using namespace std::chrono_literals;

int main() {
  constexpr auto kBusPath = "/dev/i2c-1";
  pw::Result<int> result = pw::i2c::LinuxInitiator::OpenI2cBus(kBusPath);
  if (!result.ok()) {
    PW_LOG_ERROR("Failed to open I2C bus [%s]", kBusPath);
    // return result.status();
    return 1;
  }
  pw::i2c::LinuxInitiator initiator(*result);
  std::array<std::byte, 8> buffer;
  constexpr auto kDeviceAddress = pw::i2c::Address::SevenBit<0x00>();
  pw::i2c::Device device(initiator, kDeviceAddress);
  device.ReadFor(buffer, 1ms);
  for (auto& byte : buffer) {
    PW_LOG_INFO("%x", static_cast<unsigned int>(byte));
  }
  PW_LOG_INFO("Goodbye!");
  return 0;
}

// namespace {
// 
// TEST(I2CTestSuite, I2CWriteTestCase) {
//   constexpr pw::i2c::Address kAddress = pw::i2c::Address::SevenBit<0x01>();
//   constexpr auto kExpectedWrite = pw::bytes::Array<1, 2, 3>();
//   auto expected_transactions = pw::i2c::MakeExpectedTransactionArray(
//     {pw::i2c::WriteTransaction(pw::OkStatus(), kAddress, kExpectedWrite, 1ms)}
//   );
//   pw::i2c::MockInitiator initiator(expected_transactions);
//   pw::ConstByteSpan kActualWrite = pw::bytes::Array<1, 2, 3>();
//   pw::Status status = initiator.WriteFor(kAddress, kActualWrite, 1ms);
//   if (status.ok()) {
//     PW_LOG_INFO("OK");
//   } else { 
//     PW_LOG_INFO("NOT OK");
//   }
//   // SUCCEED();
//   // FAIL();
//   EXPECT_EQ(initiator.Finalize(), pw::OkStatus());
// }
// 
// }
