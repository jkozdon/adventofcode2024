#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day09
{

void part1(const std::string &input, const bool test)
{
  uint64_t res = 0;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 1928L);
  }
}

void part2(const std::string &input, const bool test)
{
  uint64_t res = 0;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 0);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 9, test);
  fmt::println("Day 09:");
  part1(input, test);
  part2(input, test);
}

} // namespace day09
