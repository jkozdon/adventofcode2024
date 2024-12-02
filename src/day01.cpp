#include "common.hpp"
#include "fmt/core.h"
#include <ranges>
#include <set>
#include <unordered_map>
#include <cassert>

namespace day01
{

void part1(const std::string &input, const bool test)
{
  std::multiset<int> left, right;

  auto lines = input | std::views::split('\n');
  for (auto line : lines) {
    if (line.empty()) {
      break;
    }
    int a, b;
    std::istringstream ss(std::ranges::to<std::string>(line));
    ss >> a >> b;
    left.insert(a);
    right.insert(b);
  }
  uint res = 0;
  int i = 0;
  for (const auto &[a, b] : std::ranges::views::zip(left, right)) {
    res += std::abs(a - b);
  }
  fmt::println("  Part a: {}", res);
  if (test) {
    assert(res == 11);
  }
}

void part2(const std::string &input, const bool test)
{
  std::unordered_map<int, int> left;
  std::unordered_map<int, int> right;

  auto lines = input | std::views::split('\n');
  for (auto line : lines) {
    if (line.empty()) {
      break;
    }
    int a, b;
    std::istringstream ss(std::ranges::to<std::string>(line));
    ss >> a >> b;
    left[a]++;
    right[b]++;
  }
  int res = 0;
  for (auto [a, ca] : left) {
    res += a * ca * right[a];
  }
  fmt::println("  Part b: {}", res);
  if (test) {
    assert(res == 31);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 1, test);
  fmt::println("Day 01:");
  part1(input, test);
  part2(input, test);
}

} // namespace day01
