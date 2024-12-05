#include "common.hpp"
#include "fmt/core.h"

#include <ranges>
#include <vector>
#include <cassert>

namespace day04
{

template <int ix, int iy, char next>
int check(const std::vector<std::string> &lines, int i, int j)
{
  i += ix;
  j += iy;
  if (i < 0 || i >= lines.size() || j < 0 || j >= lines[i].size()) {
    return 0;
  }
  if (lines[i][j] == next) {
    if constexpr (next == 'M') {
      return check<ix, iy, 'A'>(lines, i, j);
    } else if constexpr (next == 'A') {
      return check<ix, iy, 'S'>(lines, i, j);
    } else {
      return 1;
    }
  }
  return 0;
};
void part1(const std::string &input, const bool test)
{
  auto count_xmas = [](const std::vector<std::string> &lines, int i, int j) {
    int res = 0;
    res += check<1, -1, 'M'>(lines, i, j);
    res += check<0, -1, 'M'>(lines, i, j);
    res += check<-1, -1, 'M'>(lines, i, j);
    res += check<1, 0, 'M'>(lines, i, j);
    res += check<0, 0, 'M'>(lines, i, j);
    res += check<-1, 0, 'M'>(lines, i, j);
    res += check<1, 1, 'M'>(lines, i, j);
    res += check<0, 1, 'M'>(lines, i, j);
    res += check<-1, 1, 'M'>(lines, i, j);
    return res;
  };
  auto lines = input | std::views::split('\n') |
               std::views::transform([](auto line) {
                 return std::ranges::to<std::string>(line);
               }) |
               std::ranges::to<std::vector<std::string>>();

  int res = 0;
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (lines[i][j] == 'X') {
        res += count_xmas(lines, i, j);
      }
    }
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 18);
  }
}

void part2(const std::string &input, const bool test)
{
  auto lines = input | std::views::split('\n') |
               std::views::transform([](auto line) {
                 return std::ranges::to<std::string>(line);
               }) |
               std::ranges::to<std::vector<std::string>>();

  int res = 0;
  for (int i = 1; i < lines.size() - 1; i++) {
    for (int j = 1; j < lines[i].size() - 1; j++) {
      if (lines[i][j] == 'A') {
        if (((lines[i + 1][j - 1] == 'M' && lines[i - 1][j + 1] == 'S') ||
             (lines[i + 1][j - 1] == 'S' && lines[i - 1][j + 1] == 'M')) &&
            ((lines[i + 1][j + 1] == 'M' && lines[i - 1][j - 1] == 'S') ||
             (lines[i + 1][j + 1] == 'S' && lines[i - 1][j - 1] == 'M'))) {
          ++res;
        }
      }
    }
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 9);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 4, test);
  fmt::println("Day 04:");
  part1(input, test);
  part2(input, test);
}

} // namespace day04
