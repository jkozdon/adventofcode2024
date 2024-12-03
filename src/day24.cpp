#include "common.hpp"
#include "fmt/core.h"

#include <cassert>

namespace day24
{

void part1(const std::string &input, const bool test)
{
  int res = 0;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 0);
  }
}

void part2(const std::string &input, const bool test)
{
  int res = 0;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 0);
  }
}

void run(const std::string &base_path, const bool test)
{
  return;
  auto input = read_input(base_path, 24, test);
  fmt::println("Day 24:");
  part1(input, test);
  part2(input, test);
}

} // namespace day24
