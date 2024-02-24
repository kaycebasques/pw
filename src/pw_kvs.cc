#include <cstddef>

#include "pw_kvs/flash_test_partition.h"
#include "pw_kvs/key_value_store.h"
#include "pw_sys_io/sys_io.h"

// Based off fake_flash_64_aligned_partition
// https://cs.opensource.google/pigweed/pigweed/+/master:pw_kvs/BUILD.bazel;l=197
constexpr size_t kMaxSectors = 6;
constexpr size_t kMaxEntries = 64;
// https://pigweed.googlesource.com/pigweed/sample_project/+/refs/tags/hackaday-remoticon-2020/workshop/04-kvs/main.cc
static constexpr pw::kvs::EntryFormat kvs_format = {
  .magic = 0xd253a8a9,
  .checksum = nullptr
};

pw::kvs::KeyValueStoreBuffer<kMaxEntries, kMaxSectors> kvs(
  &pw::kvs::FlashTestPartition(),
  kvs_format
);

int main() {
  std::byte in;
  kvs.Init();
  while (true) {
    pw::sys_io::ReadByte(&in).IgnoreError();
    kvs.Put("in", in);
    std::byte out;
    kvs.Get("in", &out);
    pw::sys_io::WriteByte(out).IgnoreError();
  }
  return 0;
}
