#include <queue>
#include <ranges>
#include <regex>
#include <string>
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
    std::queue<std::string> order;
    auto line = std::ranges::to<std::string>(vline);
    int c = 0;
    int l = 1;
    while (c < line.size()) {
      if (c + l > line.size()) {
        if (order.empty()) {
          break;
        }
        l = order.front().size() + 1;
        c -= order.front().size();
        order.pop();
      }
      if (towels.contains(line.substr(c, l))) {
        order.push(line.substr(c, l));
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
  int res = 0;
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 0);
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
