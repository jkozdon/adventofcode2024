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
    res += std::stoi((*match)[1].str()) *
           std::stoi((*match)[2].str());
  }
  fmt::println("  Part a: {}", res);
  if (test) {
    assert(res == 161);
  }
}

void part2(const std::string &input, const bool test)
{
  std::regex regex(R"((mul\(([0-9]+),([0-9]+)\)|do\(\)|don't\(\)))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  int res = 0;
  bool enable = true;
  for (; match != std::sregex_iterator(); ++match) {
    if ((*match).str() == "do()") {
      enable = true;
    } else if ((*match).str() == "don't()") {
      enable = false;
    } else if (enable) {
      res += std::stoi((*match)[2].str()) *
             std::stoi((*match)[3].str());
    }
  }
  fmt::println("  Part b: {}", res);
  if (test) {
    assert(res == 48);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 3, test);
  fmt::println("Day 03:");
  part1(input, test);
  part2(input, test);
}

} // namespace day03
