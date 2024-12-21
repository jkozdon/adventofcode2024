#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
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
  std::unordered_map<char, std::vector<uint64_t>> levels;

  Maze(const std::string &m) : map(m)
  {
    Nx = m.find("\n") + 1;
    Ny = m.size() / Nx;
  }

  void init_levels()
  {
    levels['N'].resize(Nx * Ny, UINT64_MAX);
    levels['S'].resize(Nx * Ny, UINT64_MAX);
    levels['E'].resize(Nx * Ny, UINT64_MAX);
    levels['W'].resize(Nx * Ny, UINT64_MAX);
  }

  bool insert_level(int x, int y, char dir, uint64_t cost)
  {
    if (levels[dir][x + y * Nx] > cost) {
      levels[dir][x + y * Nx] = cost;
      return true;
    } else {
      return false;
    }
  }

  uint64_t get_level(int x, int y, char dir)
  {
    if (x >= 0 && x < Nx - 1 && y >= 0 && y < Ny) {
      return levels[dir][x + y * Nx];
    } else {
      return UINT64_MAX;
    }
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
struct PairHash {
  std::size_t operator()(const std::pair<int, int> &p) const
  {
    return static_cast<std::size_t>(p.first + 1024 * p.second);
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
  Maze map(input);
  map.init_levels();

  constexpr uint64_t turncost = 1000;

  std::multimap<uint64_t, std::tuple<int, int, char>> moves;
  auto [sx, sy] = map.start();
  if (map(sx, sy - 1) == '.') {
    moves.insert({turncost, {sx, sy, 'N'}});
  }
  if (map(sx + 1, sy) == '.') {
    moves.insert({0, {sx, sy, 'E'}});
  }

  uint64_t score = UINT64_MAX;
  auto check_insert = [&](int x, int y, char dir, uint64_t cost = 0) {
    auto helper = [&](int x, int y, char dir, uint64_t delta) {
      auto nx = dir == 'E' ? x + 1 : dir == 'W' ? x - 1 : x;
      auto ny = dir == 'N' ? y - 1 : dir == 'S' ? y + 1 : y;
      if (map(nx, ny) != '#' && map.insert_level(x, y, dir, cost + delta)) {
        assert(!map.insert_level(x, y, dir, cost + delta));
        map.get_level(x, y, dir);
        moves.insert({cost + delta, {x, y, dir}});
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

  while (!moves.empty() && (*moves.begin()).first <= score) {
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
    }
    check_insert(x, y, dir, cur);
  }

  moves.clear();
  auto [ex, ey] = map.end();
  std::unordered_set<std::pair<int, int>, PairHash> seen;
  seen.insert({ex, ey});
  seen.insert({sx, sy});
  if (map.get_level(ex, ey + 1, 'N') == score - 1) {
    moves.insert({score, {ex, ey, 'N'}});
  }
  if (map.get_level(ex - 1, ey, 'E') == score - 1) {
    moves.insert({score, {ex, ey, 'E'}});
  }

  while (!moves.empty()) {
    auto keyval = *moves.begin();
    moves.erase(moves.begin());
    auto cur = keyval.first;
    auto dir = std::get<2>(keyval.second);
    auto x = std::get<0>(keyval.second);
    auto y = std::get<1>(keyval.second);
    auto cx = dir == 'E' ? x - 1 : dir == 'W' ? x + 1 : x;
    auto cy = dir == 'N' ? y + 1 : dir == 'S' ? y - 1 : y;
    seen.insert({x, y});
    if (map.get_level(cx, cy, dir) == cur - 1) {
      moves.insert({cur - 1, {cx, cy, dir}});
    }
    if (dir == 'N' || dir == 'S') {
      if (map.get_level(x - 1, y, 'E') == cur - turncost - 1) {
        moves.insert({cur - turncost - 1, {x - 1, y, 'E'}});
      }
      if (map.get_level(x + 1, y, 'W') == cur - turncost - 1) {
        moves.insert({cur - turncost - 1, {x + 1, y, 'W'}});
      }
    }
    if (dir == 'E' || dir == 'W') {
      if (map.get_level(x, y - 1, 'S') == cur - turncost - 1) {
        moves.insert({cur - turncost - 1, {x, y - 1, 'S'}});
      }
      if (map.get_level(x, y + 1, 'N') == cur - turncost - 1) {
        moves.insert({cur - turncost - 1, {x, y + 1, 'N'}});
      }
    }
  }

  int res = seen.size();
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 64);
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
