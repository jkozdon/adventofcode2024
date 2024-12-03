#include <ranges>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day02
{

void part1(const std::string &input, const bool test)
{
  auto lines = input | std::views::split('\n');
  int res = 0;
  for (auto line : lines) {
    if (line.empty()) {
      break;
    }
    int next{};
    int last{};
    std::istringstream ss(std::ranges::to<std::string>(line));
    ss >> last;
    ss >> next;
    bool increasing = next > last;
    bool valid = true;
    do {
      auto delta = std::abs(last - next);
      valid =
          0 < delta && delta < 4 && (increasing ? next > last : next < last);
      last = next;
    } while (valid && ss >> next);
    res += valid;
  }
  fmt::println("  Part a: {}", res);
  if (test) {
    assert(res == 2);
  }
}

void part2(const std::string &input, const bool test) {}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 2, test);
  fmt::println("Day 02:");
  part1(input, test);
  part2(input, test);
}

} // namespace day02
