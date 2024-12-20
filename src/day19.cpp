#include <ranges>
#include <regex>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day19
{

void part1(const std::string &input, const bool test)
{
  std::unordered_set<std::string> towels;
  std::regex regex(R"(([a-z]+)([, ]?))");
  auto newline_pos = input.find('\n');
  std::string first_line = input.substr(0, newline_pos);
  auto match =
      std::sregex_iterator(first_line.begin(), first_line.end(), regex);

  for (auto it = match; it != std::sregex_iterator(); ++it) {
    towels.insert((*it)[1]);
  }
  int res = 0;

  auto lines =
      input | std::ranges::views::split('\n') | std::ranges::views::drop(2);
  for (auto vline : lines) {
    if (vline.empty())
      continue;
    std::stack<std::pair<int, int>> order;
    auto line = std::ranges::to<std::string>(vline);
    int c = 0;
    int l = 1;
    while (c < line.size()) {
      if (c + l > line.size()) {
        if (order.empty()) {
          break;
        }
        c = order.top().first;
        l = order.top().second;
        order.pop();
      }
      if (towels.contains(line.substr(c, l))) {
        order.push({c, l + 1});
        c += l;
        l = 1;
      } else {
        ++l;
      }
    }
    res += c == line.size();
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 6);
  }
}

void part2(const std::string &input, const bool test)
{
  std::unordered_set<std::string> towels;
  std::regex regex(R"(([a-z]+)([, ]?))");
  auto newline_pos = input.find('\n');
  std::string first_line = input.substr(0, newline_pos);
  auto match =
      std::sregex_iterator(first_line.begin(), first_line.end(), regex);

  for (auto it = match; it != std::sregex_iterator(); ++it) {
    towels.insert((*it)[1]);
  }
  uint64_t res = 0;

  auto lines =
      input | std::ranges::views::split('\n') | std::ranges::views::drop(2);
  for (auto vline : lines) {
    if (vline.empty())
      continue;
    auto line = std::ranges::to<std::string>(vline);
    std::unordered_map<int, uint64_t> found;
    found[0] = 1;
    for (int i = 1; i <= line.size(); ++i) {
      for (auto t : towels) {
        auto l = t.size();
        if (l <= i) {
          if (line.substr(i - l, l) == t) {
            found[i] += found[i - l];
          }
        }
      }
    }
    res += found[line.size()];
  }

  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 16);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 19, test);
  fmt::println("Day 19:");
  part1(input, test);
  part2(input, test);
}

} // namespace day19
