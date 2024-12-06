#include <list>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day05
{

void part1(const std::string &input, const bool test)
{
  std::unordered_map<int, std::unordered_set<int>> links;

  auto lines = input | std::views::split('\n');
  auto next_line = lines.begin();
  for (; !(*next_line).empty(); ++next_line) {
    auto line = *next_line;
    std::istringstream ss(std::ranges::to<std::string>(line));
    int a, b;
    char sep;
    ss >> a >> sep >> b;
    links[a].insert(b);
  }
  for (; (*next_line).empty(); ++next_line)
    ;
  int res = 0;
  for (; !(*next_line).empty(); ++next_line) {
    auto line = *next_line;
    std::istringstream ss(std::ranges::to<std::string>(line));
    int a;
    char sep;
    std::unordered_set<int> seen;
    bool valid = true;
    int midpnt = (line.size() / 3) / 2;
    int mid{};
    do {
      ss >> a >> sep;
      for (auto b : seen) {
        valid = valid & !(links[a].contains(b));
      }
      seen.insert(a);
      if (midpnt == 0)
        mid = a;
      --midpnt;
    } while (ss && valid);
    res += valid ? mid : 0;
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 143);
  }
}

void part2(const std::string &input, const bool test)
{
  std::unordered_map<int, std::unordered_set<int>> links;

  auto lines = input | std::views::split('\n');
  auto next_line = lines.begin();
  for (; !(*next_line).empty(); ++next_line) {
    auto line = *next_line;
    std::istringstream ss(std::ranges::to<std::string>(line));
    int a, b;
    char sep;
    ss >> a >> sep >> b;
    links[a].insert(b);
  }
  for (; (*next_line).empty(); ++next_line)
    ;
  int res = 0;
  for (; !(*next_line).empty(); ++next_line) {
    auto line = *next_line;
    std::istringstream ss(std::ranges::to<std::string>(line));
    int a;
    char sep;
    std::list<int> seen;
    bool valid = true;
    do {
      ss >> a >> sep;
      auto b = seen.begin();
      for (; b != seen.end(); ++b) {
        if (links[a].contains(*b)) {
          valid = false;
          break;
        }
      }
      seen.insert(b, a);
    } while (ss);
    if (!valid) {
      int midpnt = (line.size() / 3) / 2;
      for (auto b : seen) {
        if (midpnt == 0) {
          res += b;
          break;
        }
        --midpnt;
      }
    }
  }

  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 123);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 5, test);
  fmt::println("Day 05:");
  part1(input, test);
  part2(input, test);
}

} // namespace day05
