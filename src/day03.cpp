#include "common.hpp"
#include "fmt/core.h"

namespace day03
{

void part1(const std::string &input, const bool test) {}

void part2(const std::string &input, const bool test) {}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 3, test);
  fmt::println("Day 03:");
  part1(input, test);
  part2(input, test);
}

} // namespace day03
