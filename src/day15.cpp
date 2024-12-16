#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day15
{

void part1(const std::string &input, const bool test)
{
  std::string map = input;

  int Nx = map.find("\n");
  int ri = map.find("@");
  int rx{ri % (Nx + 1)};
  int ry{ri / (Nx + 1)};
  fmt::println("Nx = {}", Nx);
  fmt::println("rx, ry = {} {}", rx, ry);
  for (int m = map.find("\n\n") + 2; m < map.size(); ++m) {
    auto move = map[m];
    if (move == '\n') {
      continue;
    }

    int sx{0}, sy{0};
    if (move == '<') {
      sx = -1;
    } else if (move == '>') {
      sx = +1;
    } else if (move == 'v') {
      sy = +1;
    } else if (move == '^') {
      sy = -1;
    }

    int tx{rx + sx}, ty{ry + sy};
    auto s = map[tx + ty * (Nx + 1)];
    if (s == '.') {
      map[rx + (Nx + 1) * ry] = '.';
      rx += sx;
      ry += sy;
      map[rx + (Nx + 1) * ry] = '@';
    } else if (s == 'O') {
      do {
        tx += sx;
        ty += sy;
      } while (map[tx + ty * (Nx + 1)] == 'O');
      if (map[tx + ty * (Nx + 1)] == '.') {
        map[rx + (Nx + 1) * ry] = '.';
        map[tx + ty * (Nx + 1)] = 'O';
        map[rx + sx + (ry + sy) * (Nx + 1)] = '.';
        rx += sx;
        ry += sy;
        map[rx + (Nx + 1) * ry] = '@';
      }
    }
  }
  int res = 0;
  for (int pos = map.find("O", 0); pos != std::string::npos;
       pos = map.find("O", pos + 1)) {
    int ix{pos % (Nx + 1)}, iy{pos / (Nx + 1)};
    res += ix + iy * 100;
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 10092);
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
  auto input = read_input(base_path, 15, test);
  fmt::println("Day 15:");
  part1(input, test);
  part2(input, test);
}

} // namespace day15
