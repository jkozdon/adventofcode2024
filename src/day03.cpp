#include "common.hpp"
#include "fmt/core.h"

#include <regex>
#include <string>
#include <cassert>

namespace day03
{

void part1(const std::string &input, const bool test)
{
  std::regex regex(R"(mul\(([0-9]+),([0-9]+)\))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  int res = 0;
  for (; match != std::sregex_iterator(); ++match) {
    res += std::atoi((*match)[1].str().c_str()) *
           std::atoi((*match)[2].str().c_str());
  }
  fmt::println("  Part a: {}", res);
  if (test) {
    assert(res == 161);
  }
}

void part2(const std::string &input, const bool test) {}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 3, test);
  fmt::println("Day 03:");
  part1(input, test);
  part2(input, test);
}

} // namespace day03
