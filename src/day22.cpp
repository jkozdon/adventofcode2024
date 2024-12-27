#include <cassert>
#include <climits>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <ranges>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

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
    assert(res == 37990510L);
  }
}

struct TupleHash {
  std::size_t operator()(const std::tuple<int, int, int, int> &p) const
  {
    return static_cast<std::size_t>(std::get<0>(p) + 100 * std::get<1>(p) +
                                    100 * 100 * std::get<2>(p) +
                                    100 * 100 * 100 * std::get<3>(p));
  }
};
void part2(const std::string &input, const bool test)
{
  auto mix_prune = [](uint64_t a, uint64_t b) { return (a ^ b) % 16777216; };
  auto lines = input | std::ranges::views::split('\n');
  uint64_t res{0};
  std::unordered_map<std::tuple<int, int, int, int>, int, TupleHash> patterns;
  for (auto line : lines) {
    if (line.empty()) {
      continue;
    }
    uint64_t num = std::atol(std::ranges::to<std::string>(line).c_str());
    std::unordered_set<std::tuple<int, int, int, int>, TupleHash> seen;
    int delta1{INT_MAX};
    int delta2{INT_MAX};
    int delta3{INT_MAX};
    int delta4{INT_MAX};
    for (int i = 0; i < 2000; ++i) {
      auto back = num;
      num = mix_prune(num, num * 64);
      num = mix_prune(num, num / 32);
      num = mix_prune(num, num * 2048);
      delta1 = delta2;
      delta2 = delta3;
      delta3 = delta4;
      delta4 = num % 10 - back % 10;
      std::tuple delta = {delta1, delta2, delta3, delta4};
      if (!seen.contains(delta)) {
        seen.insert(delta);
        patterns[delta] += num % 10;
        res = res < patterns[delta] ? patterns[delta] : res;
      }
    }
  }
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 23);
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
