#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <array>
#include <vector>

namespace day20
{

void part1(const std::string &input, const bool test)
{
  auto Nx = input.find('\n') + 1;
  auto Ny = input.size() / Nx;
  std::vector<uint64_t> path;
  path.resize(Nx * Ny, UINT64_MAX);
  auto start = input.find('S');
  auto end = input.find('E');

  auto coord2index = [=](int x, int y) { return x + y * Nx; };
  auto index2coord = [=](int ind) { return std::pair(ind % Nx, ind / Nx); };
  auto open = [&](int x, int y) {
    auto index = coord2index(x, y);
    return path[index] == UINT64_MAX && input[index] != '#';
  };
  auto get_lvl = [&](int x, int y) {
    if (x >= 0 && x < Nx && y >= 0 && y < Ny) {
      auto index = coord2index(x, y);
      return path[index];
    } else {
      return UINT64_MAX;
    }
  };

  auto jump_threshold = test ? 20 : 100;

  auto [x, y] = index2coord(start);
  uint64_t lvl = path[start] = 0;
  int res = 0;
  while (coord2index(x, y) != end) {
    if (open(x + 1, y)) {
      x = x + 1;
    } else if (open(x - 1, y)) {
      x = x - 1;
    } else if (open(x, y + 1)) {
      y = y + 1;
    } else if (open(x, y - 1)) {
      y = y - 1;
    } else {
      fmt::println("No open paths! ({}, {}) lvl: {}", x, y, lvl);
      break;
    }
    std::array<uint64_t, 4> jumps = {get_lvl(x, y + 2), get_lvl(x, y - 2),
                                     get_lvl(x + 2, y), get_lvl(x - 2, y)};
    for (auto l : jumps) {
      if (l != UINT64_MAX && lvl - l >= jump_threshold) {
        ++res;
      }
    }
    path[coord2index(x, y)] = ++lvl;
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 5);
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
  auto input = read_input(base_path, 20, test);
  fmt::println("Day 20:");
  part1(input, test);
  part2(input, test);
}

} // namespace day20
