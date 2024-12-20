#include <map>
#include <unordered_set>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

namespace day16
{

struct Maze {
  int Nx;
  int Ny;
  std::string map;

  Maze(const std::string &m) : map(m)
  {
    Nx = m.find("\n") + 1;
    Ny = m.size() / Nx;
  }

  std::pair<int, int> start() { return {1, Ny - 2}; }
  std::pair<int, int> end() { return {Nx - 3, 1}; }

  char index(int x, int y) { return x + y * Nx; }
  char operator()(int x, int y) const
  {
    if (x >= 0 && x < Nx - 1 && y >= 0 && y < Ny) {
      return map[x + y * Nx];
    } else {
      return '#';
    }
  }

  char operator()(std::pair<int, int> coord) const
  {
    return (*this)(coord.first, coord.second);
  }
};

struct TupleHash {
  std::size_t operator()(const std::tuple<int, int, char> &p) const
  {
    return static_cast<std::size_t>(std::get<0>(p) + 1024 * std::get<1>(p) +
                                    1024 * 1024 * std::get<2>(p));
  }
};

void part1(const std::string &input, const bool test)
{
  Maze map(input);

  constexpr uint64_t turncost = 1000;

  std::multimap<uint64_t, std::tuple<int, int, char>> moves;
  auto [sx, sy] = map.start();
  if (map(sx, sy - 1) == '.') {
    moves.insert({turncost, {sx, sy, 'N'}});
  }
  if (map(sx + 1, sy) == '.') {
    moves.insert({0, {sx, sy, 'E'}});
  }

  std::unordered_set<std::tuple<int, int, char>, TupleHash> seen;
  uint64_t score = UINT64_MAX;
  auto check_insert = [&](int x, int y, char dir, uint64_t cost = 0) {
    auto helper = [&](int x, int y, char dir, uint64_t delta) {
      auto nx = dir == 'E' ? x + 1 : dir == 'W' ? x - 1 : x;
      auto ny = dir == 'N' ? y - 1 : dir == 'S' ? y + 1 : y;
      if (map(nx, ny) != '#' && !seen.contains({x, y, dir})) {
        moves.insert({cost + delta, {x, y, dir}});
        seen.insert({x, y, dir});
      }
    };
    auto nx = dir == 'E' ? x + 1 : dir == 'W' ? x - 1 : x;
    if (dir == 'N' || dir == 'S') {
      helper(x, y, dir, 0);
      helper(x, y, 'E', turncost);
      helper(x, y, 'W', turncost);
    } else {
      helper(x, y, dir, 0);
      helper(x, y, 'N', turncost);
      helper(x, y, 'S', turncost);
    }
  };

  while (!moves.empty()) {
    auto keyval = *moves.begin();
    moves.erase(moves.begin());
    auto cur = keyval.first;
    auto dir = std::get<2>(keyval.second);
    auto x = std::get<0>(keyval.second);
    auto y = std::get<1>(keyval.second);
    x = dir == 'E' ? x + 1 : dir == 'W' ? x - 1 : x;
    y = dir == 'N' ? y - 1 : dir == 'S' ? y + 1 : y;
    ++cur;
    if (map(x, y) == 'E') {
      score = cur;
      break;
    }
    check_insert(x, y, dir, cur);
  }

  fmt::print("  Part a: {}\n", score);
  if (test) {
    assert(score == 11048);
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
  auto input = read_input(base_path, 16, test);
  fmt::println("Day 16:");
  part1(input, test);
  part2(input, test);
}

} // namespace day16
