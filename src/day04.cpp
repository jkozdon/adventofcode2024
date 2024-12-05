#include "common.hpp"
#include "fmt/core.h"

#include <ranges>
#include <utility>
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

template <int ix = -1, int iy = -1>
int check_all(const std::vector<std::string> &lines, int i, int j)
{
  if constexpr (ix == 2 || iy == 2) {
    return 0;
  } else {
    int res = check<ix, iy, 'M'>(lines, i, j);
    constexpr int nx = iy < 1 ? ix : ix + 1;
    constexpr int ny = iy < 1 ? iy + 1 : -1;
    return res + check_all<nx, ny>(lines, i, j);
  }
}

template <int... ixs> void part1(const std::string &input, const bool test)
{
  auto lines = input | std::views::split('\n') |
               std::views::transform([](auto line) {
                 return std::ranges::to<std::string>(line);
               }) |
               std::ranges::to<std::vector<std::string>>();

  std::integer_sequence<int, -1, 0, 1> vals;
  int res = 0;
  for (int i = 0; i < lines.size(); i++) {
    for (int j = 0; j < lines[i].size(); j++) {
      if (lines[i][j] == 'X') {
        res += check_all(lines, i, j);
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
