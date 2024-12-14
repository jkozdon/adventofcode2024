#include <regex>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

namespace day13
{

void part1(const std::string &input, const bool test)
{
  std::regex regex(R"(Button A: X\+(\d+), Y\+(\d+)\n)"
                   R"(Button B: X\+(\d+), Y\+(\d+)\n)"
                   R"(Prize: X=(\d+), Y=(\d+))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  int res = 0;
  for (; match != std::sregex_iterator(); ++match) {
    int a11 = std::stoi((*match)[1].str());
    int a12 = std::stoi((*match)[3].str());
    int a21 = std::stoi((*match)[2].str());
    int a22 = std::stoi((*match)[4].str());
    int b1 = std::stoi((*match)[5].str());
    int b2 = std::stoi((*match)[6].str());
    if (a11 * a22 != a12 * a21) {
      int d = a11 * a22 - a12 * a21;
      int x1 = (a22 * b1 - a12 * b2) / d;
      int x2 = (-a21 * b1 + a11 * b2) / d;
      if (x1 >= 0 && x2 >= 0 && a11 * x1 + a12 * x2 == b1 &&
          a21 * x1 + a22 * x2 == b2) {
        res += 3 * x1 + x2;
      }
    } else {
      fmt::println("no unique soln to one equation");
      return;
    };
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 480);
  }
}

void part2(const std::string &input, const bool test)
{
  std::regex regex(R"(Button A: X\+(\d+), Y\+(\d+)\n)"
                   R"(Button B: X\+(\d+), Y\+(\d+)\n)"
                   R"(Prize: X=(\d+), Y=(\d+))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  uint64_t res = 0;
  for (; match != std::sregex_iterator(); ++match) {
    int64_t a11 = std::stoi((*match)[1].str());
    int64_t a12 = std::stoi((*match)[3].str());
    int64_t a21 = std::stoi((*match)[2].str());
    int64_t a22 = std::stoi((*match)[4].str());
    int64_t b1 = std::stoi((*match)[5].str()) + 10000000000000;
    int64_t b2 = std::stoi((*match)[6].str()) + 10000000000000;
    if (a11 * a22 != a12 * a21) {
      int64_t d = a11 * a22 - a12 * a21;
      int64_t x1 = (a22 * b1 - a12 * b2) / d;
      int64_t x2 = (-a21 * b1 + a11 * b2) / d;
      if (x1 >= 0 && x2 >= 0 && a11 * x1 + a12 * x2 == b1 &&
          a21 * x1 + a22 * x2 == b2) {
        res += 3 * x1 + x2;
      }
    } else {
      fmt::println("no unique soln to one equation");
      return;
    };
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 875318608908L);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 13, test);
  fmt::println("Day 13:");
  part1(input, test);
  part2(input, test);
}

} // namespace day13
