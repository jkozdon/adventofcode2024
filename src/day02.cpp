#include "common.hpp"
#include "fmt/core.h"

namespace day02
{

void part1(const std::string &input, const bool test) {}

void part2(const std::string &input, const bool test) {}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 1, test);
  fmt::println("Day 02:");
  part1(input, test);
  part2(input, test);
}

} // namespace day02
