#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <ranges>
#include <string>

namespace day22
{

void part1(const std::string &input, const bool test)
{
  auto mix_prune = [](uint64_t a, uint64_t b) { return (a ^ b) % 16777216; };
  auto lines = input | std::ranges::views::split('\n');
  uint64_t res{0};
  for (auto line : lines) {
    if (line.empty()) {
      continue;
    }
    uint64_t num = std::atol(std::ranges::to<std::string>(line).c_str());
    for (int i = 0; i < 2000; ++i) {
      num = mix_prune(num, num * 64);
      num = mix_prune(num, num / 32);
      num = mix_prune(num, num * 2048);
    }
    res += num;
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 37327623L);
  }
}

void part2(const std::string &input, const bool test)
{
  int res = 0;
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 0);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 22, test);
  fmt::println("Day 22:");
  part1(input, test);
  part2(input, test);
}

} // namespace day22
