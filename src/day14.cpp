#include <iostream>
#include <regex>
#include <cassert>
#include <climits>

#include "common.hpp"
#include "fmt/core.h"
#include <tuple>
#include <unistd.h>
#include <vector>

namespace day14
{

void part1(const std::string &input, const bool test)
{
  int sx = test ? 11 : 101;
  int sy = test ? 7 : 103;
  int t = 100;

  std::regex regex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  int q11 = 0;
  int q12 = 0;
  int q21 = 0;
  int q22 = 0;
  for (; match != std::sregex_iterator(); ++match) {
    int lx = std::stoi((*match)[1].str());
    int ly = std::stoi((*match)[2].str());
    int vx = std::stoi((*match)[3].str());
    int vy = std::stoi((*match)[4].str());
    lx = ((lx + t * vx) % sx + sx) % sx;
    ly = ((ly + t * vy) % sy + sy) % sy;
    if (lx < sx / 2 && ly < sy / 2)
      ++q11;
    if (lx > sx / 2 && ly < sy / 2)
      ++q12;
    if (lx < sx / 2 && ly > sy / 2)
      ++q21;
    if (lx > sx / 2 && ly > sy / 2)
      ++q22;
  }
  int res = q11 * q12 * q21 * q22;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 12);
  }
}

void part2(const std::string &input, const bool test)
{
  int sx = test ? 11 : 101;
  int sy = test ? 7 : 103;
  int t = 0;
  std::vector<std::tuple<int, int, int, int>> robots;
  std::regex regex(R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))");
  auto match = std::sregex_iterator(input.begin(), input.end(), regex);
  for (; match != std::sregex_iterator(); ++match) {
    int lx = std::stoi((*match)[1].str());
    int ly = std::stoi((*match)[2].str());
    int vx = std::stoi((*match)[3].str());
    int vy = std::stoi((*match)[4].str());
    robots.push_back({lx, ly, vx, vy});
  }

  int min = INT_MAX;
  int tstore = 0;
  do {
    std::vector<bool> tree(sx * sy);
    for (auto [lx, ly, vx, vy] : robots) {
      lx = ((lx + t * vx) % sx + sx) % sx;
      ly = ((ly + t * vy) % sy + sy) % sy;
      tree[lx + ly * sx] = true;
    }
    auto is_tree = [&tree, sx, sy](int lx, int ly) {
      if (lx < 0 || ly < 0 || lx >= sx || ly >= sy) {
        return false;
      }
      return (bool)tree[lx + ly * sx];
    };
    int count = 0;
    for (int ly = 0; ly < sy; ++ly) {
      for (int lx = 0; lx < sx; ++lx) {
        if (!is_tree(lx, ly))
          continue;
        count += !(is_tree(lx - 1, ly - 1) || //
                   is_tree(lx + 0, ly - 1) || //
                   is_tree(lx + 1, ly - 1) || //
                                              //
                   is_tree(lx - 1, ly + 0) || //
                   is_tree(lx + 1, ly + 0) || //
                                              //
                   is_tree(lx - 1, ly + 1) || //
                   is_tree(lx + 0, ly + 1) || //
                   is_tree(lx + 1, ly + 1));
      }
    }
    if (count < min) {
      min = count;
      tstore = t;
#if 0
      for (int y = 0; y < sy; ++y) {
        for (int x = 0; x < sx; ++x) {
          fmt::print("{}", tree[x + y * sx] ? '*' : ' ');
        }
        fmt::println("");
      }
      fmt::println("{} : {}", tstore, min);
#endif
    }
    ++t;
  } while (t < 10000);

  fmt::print("  Part b: {}\n", tstore);
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 14, test);
  fmt::println("Day 14:");
  part1(input, test);
  part2(input, test);
}

} // namespace day14
