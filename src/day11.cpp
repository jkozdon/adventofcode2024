#include <ranges>
#include <string>
#include <unordered_map>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

struct hash_pair {
  size_t operator()(const std::pair<uint64_t, int> &p) const
  {
    return (size_t)(p.first + p.second * 1024);
  }
};

namespace day11
{

uint64_t count_nums(
    const int blinks, const uint64_t num,
    std::unordered_map<std::pair<uint64_t, int>, uint64_t, hash_pair> &found)
{
  const std::pair key = {num, blinks};
  if (found.contains(key)) {
    return found[key];
  }
  uint64_t count = 0;
  if (blinks == 0) {
    count = 1;
  } else if (num == 0) {
    count = count_nums(blinks - 1, 1, found);
  } else {
    auto tmp = num;
    int digits = 0;
    for (; tmp > 0; tmp /= 10, ++digits) {
    }
    if (digits % 2 == 0) {
      auto scale = 1;
      for (int d = 0; d < digits / 2; ++d, scale *= 10) {
      }
      count = count_nums(blinks - 1, num / scale, found) +
              count_nums(blinks - 1, num % scale, found);
    } else {
      count = count_nums(blinks - 1, num * 2024, found);
    }
  }
  found[key] = count;
  return count;
}

void part1(const std::string &input, const bool test)
{
  constexpr int n_reps = 25;

  auto str_nums = input | std::ranges::views::split(' ');
  std::unordered_map<std::pair<uint64_t, int>, uint64_t, hash_pair> found;

  uint64_t res = 0;
  for (auto str_num : str_nums) {
    auto num = std::stoi(std::string{str_num.begin(), str_num.end()});
    res += count_nums(n_reps, num, found);
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 55312);
  }
}

void part2(const std::string &input, const bool test)
{
  constexpr int n_reps = 75;

  auto str_nums = input | std::ranges::views::split(' ');
  std::unordered_map<std::pair<uint64_t, int>, uint64_t, hash_pair> found;

  uint64_t res = 0;
  for (auto str_num : str_nums) {
    auto num = std::stoi(std::string{str_num.begin(), str_num.end()});
    res += count_nums(n_reps, num, found);
  }

  fmt::print("  Part b: {}\n", res);
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 11, test);
  fmt::println("Day 11:");
  part1(input, test);
  part2(input, test);
}

} // namespace day11
