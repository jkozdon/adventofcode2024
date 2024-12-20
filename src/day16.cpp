#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <map>
#include <unordered_set>

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

  std::multimap<uint64_t, std::pair<std::pair<int, int>, char>> moves;
  auto [sx, sy] = map.start();
  if (map(sx, sy - 1) == '.') {
    moves.insert({turncost, {{sx, sy}, 'N'}});
  }
  if (map(sx + 1, sy) == '.') {
    moves.insert({0, {{sx, sy}, 'E'}});
  }

  std::unordered_set<std::tuple<int, int, char>, TupleHash> seen;
  uint64_t score = UINT64_MAX;
  auto check_insert = [&](int x, int y, char dir, uint64_t cost) {
    auto nx = dir == 'E' ? x + 1 : dir == 'W' ? x - 1 : x;
    auto ny = dir == 'N' ? y - 1 : dir == 'S' ? y + 1 : y;
    if (map(nx, ny) != '#' && !seen.contains({nx, ny, dir})) {
      moves.insert({cost, {{nx, ny}, dir}});
      seen.insert({nx, ny, dir});
    }
  };

  while (!moves.empty()) {
    auto keyval = *moves.begin();
    moves.erase(moves.begin());
    auto cur = keyval.first;
    auto x = keyval.second.first.first;
    auto y = keyval.second.first.second;
    auto dir = keyval.second.second;
    if (map(x, y) == 'E') {
      score = cur;
      break;
    }
    if (dir == 'N') {
      check_insert(x, y, 'N', cur + 1);
      check_insert(x, y, 'E', cur + turncost + 1);
      check_insert(x, y, 'W', cur + turncost + 1);
    }
    if (dir == 'S') {
      check_insert(x, y, 'S', cur + 1);
      check_insert(x, y, 'E', cur + turncost + 1);
      check_insert(x, y, 'W', cur + turncost + 1);
    }
    if (dir == 'E') {
      check_insert(x, y, 'E', cur + 1);
      check_insert(x, y, 'N', cur + turncost + 1);
      check_insert(x, y, 'S', cur + turncost + 1);
    }
    if (dir == 'W') {
      check_insert(x, y, 'W', cur + 1);
      check_insert(x, y, 'N', cur + turncost + 1);
      check_insert(x, y, 'S', cur + turncost + 1);
    }
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
