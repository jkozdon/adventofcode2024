#include <numeric>
#include <ranges>
#include <vector>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

namespace day07
{

bool part1_check(int64_t target, int index, auto nums)
{
  auto num = nums[index];
  if (nums.size() == index + 1) {
    return target == num;
  }
  if (target % num == 0 && part1_check(target / num, index + 1, nums)) {
    return true;
  }
  return part1_check(target - num, index + 1, nums);
}

void part1(const std::string &input, const bool test)
{
  auto results =
      input | std::views::split('\n') | std::views::transform([](auto &&line) {
        if (line.empty())
          return (int64_t)0;
        auto nums = line | std::views::split(' ') |
                    std::views::transform([](auto &&num) { //
                      auto st = num.begin();
                      auto en = num.end();
                      if (*(en - 1) == ':') {
                        --en;
                      }
                      std::string str(st, en);
                      return std::atoll(str.c_str());
                    }) |
                    std::ranges::to<std::vector<int64_t>>();
        auto target = nums[0];
        return part1_check(target, 0,
                           nums | std::views::drop(1) | std::views::reverse)
                   ? (int64_t)target
                   : (int64_t)0;
      }) |
      std::ranges::to<std::vector<int64_t>>();
  int64_t res = std::reduce(results.begin(), results.end());
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 3749);
  }
}

bool part2_check(int64_t target, int index, auto nums)
{
  auto num = nums[index];
  ++index;
  if (nums.size() == index) {
    return target == num;
  }
  if (target % num == 0 && part2_check(target / num, index, nums)) {
    return true;
  }
  auto mul = 10;
  for (; num / mul; mul *= 10) {
  }
  if (target % mul == num && part2_check(target / mul, index, nums)) {
    return true;
  }
  return part2_check(target - num, index, nums);
}

void part2(const std::string &input, const bool test)
{
  auto results =
      input | std::views::split('\n') | std::views::transform([](auto &&line) {
        if (line.empty())
          return (int64_t)0;
        auto nums = line | std::views::split(' ') |
                    std::views::transform([](auto &&num) { //
                      auto st = num.begin();
                      auto en = num.end();
                      if (*(en - 1) == ':') {
                        --en;
                      }
                      std::string str(st, en);
                      return std::atoll(str.c_str());
                    }) |
                    std::ranges::to<std::vector<int64_t>>();
        auto target = nums[0];
        return part2_check(target, 0,
                           nums | std::views::drop(1) | std::views::reverse)
                   ? (int64_t)target
                   : (int64_t)0;
      }) |
      std::ranges::to<std::vector<int64_t>>();
  int64_t res = std::reduce(results.begin(), results.end());
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 11387);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 7, test);
  fmt::println("Day 07:");
  part1(input, test);
  part2(input, test);
}

} // namespace day07
