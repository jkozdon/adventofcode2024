#include <ranges>
#include <vector>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day06
{

enum direction { up=1, down=2, right=4, left=8 };

void part1(const std::string &input, const bool test)
{

  auto lines = input | std::views::split('\n') |
               std::ranges::to<std::vector<std::string>>();
  int gx = 0;
  int gy = 0;
  [&] {
    for (auto line : lines) {
      gx = 0;
      for (auto c : line) {
        if (c == '^') {
          lines[gy][gx] = '.';
          return;
        }
        ++gx;
      }
      ++gy;
    }
  }();

  int Nx = lines[0].size();
  int Ny = lines.size();

  direction dir = up;

  int res = 0;
  while (true) {
    if (lines[gy][gx] == '.') {
      ++res;
      lines[gy][gx] = 'X';
    }
    if (dir == up) {
      if (gy == 0)
        break;
      if (lines[gy - 1][gx] != '#') {
        gy -= 1;
      } else {
        dir = right;
      }
    } else if (dir == right) {
      if (gx == Nx - 1)
        break;
      if (lines[gy][gx + 1] != '#') {
        gx += 1;
      } else {
        dir = down;
      }
    } else if (dir == down) {
      if (gy == Ny - 1)
        break;
      if (lines[gy + 1][gx] != '#') {
        gy += 1;
      } else {
        dir = left;
      }
    } else {
      if (gx == 0)
        break;
      if (lines[gy][gx - 1] != '#') {
        gx -= 1;
      } else {
        dir = up;
      }
    }
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 41);
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
  auto input = read_input(base_path, 6, test);
  fmt::println("Day 06:");
  part1(input, test);
  part2(input, test);
}

} // namespace day06
