#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day06
{

enum direction { up = 1, down = 2, right = 4, left = 8 };

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
struct hash_pair {
  size_t operator()(const std::pair<int, int> &p) const
  {
    return (size_t)(p.first + p.second * 1024);
  }
};

void part2(const std::string &input, const bool test)
{
  std::unordered_map<int, std::unordered_set<int>> rows;
  std::unordered_map<int, std::unordered_set<int>> cols;
  auto contains_loop =
      [](std::unordered_map<int, std::unordered_set<int>> &rows,
         std::unordered_map<int, std::unordered_set<int>> &cols, int gx, int gy,
         int dir) {
        std::unordered_map<std::pair<int, int>, int, hash_pair> seen;
        while (true) {
          if (dir == up) {
            const auto &col = cols[gx];
            auto m = -1;
            for (auto n : col) {
              if (gy > n) {
                m = std::max(m, n);
              }
            }
            if (m == -1) {
              return false;
            }
            gy = m + 1;
            dir = right;
          } else if (dir == right) {
            const auto &row = rows[gy];
            auto m = INT_MAX;
            for (auto n : row) {
              if (gx < n) {
                m = std::min(m, n);
              }
            }
            if (m == INT_MAX) {
              return false;
            }
            gx = m - 1;
            dir = down;
          } else if (dir == down) {
            const auto &col = cols[gx];
            auto m = INT_MAX;
            for (auto n : col) {
              if (gy < n) {
                m = std::min(m, n);
              }
            }
            if (m == INT_MAX) {
              return false;
            }
            gy = m - 1;
            dir = left;
          } else {
            const auto &row = rows[gy];
            auto m = -1;
            for (auto n : row) {
              if (gx > n) {
                m = std::max(m, n);
              }
            }
            if (m == -1) {
              return false;
            }
            gx = m + 1;
            dir = up;
          }
          const std::pair pnt{gx, gy};
          if (seen[pnt] & dir) {
            return true;
          }
          seen[pnt] |= dir;
        }
      };

  auto lines = input | std::views::split('\n') |
               std::ranges::to<std::vector<std::string>>();
  int gx = 0;
  int gy = 0;
  for (int j = 0; j < lines.size(); ++j) {
    auto &line = lines[j];
    for (int i = 0; i < line.size(); ++i) {
      auto c = line[i];
      if (c == '^') {
        gx = i;
        gy = j;
      }
      if (c == '#') {
        rows[j].insert(i);
        cols[i].insert(j);
      }
    }
  }

  int Nx = lines[0].size();
  int Ny = lines.size();

  direction dir = up;

  std::unordered_set<std::pair<int, int>, hash_pair> found;
  while (true) {
    if (dir == up) {
      int ny = gy - 1;
      int nx = gx;
      if (ny < 0)
        break;
      if (lines[ny][nx] != '#') {
        if (lines[ny][nx] == '.') {
          rows[ny].insert(nx);
          cols[nx].insert(ny);
          if (contains_loop(rows, cols, gx, gy, dir)) {
            found.insert(std::pair{nx, ny});
          }
          rows[ny].erase(nx);
          cols[nx].erase(ny);
        }
        lines[gy][gx] = 'X';
        --gy;
      } else {
        dir = right;
      }
    } else if (dir == right) {
      int ny = gy;
      int nx = gx + 1;
      if (nx == 1)
        break;
      if (lines[gy][nx] != '#') {
        if (lines[ny][nx] == '.') {
          rows[ny].insert(nx);
          cols[nx].insert(ny);
          if (contains_loop(rows, cols, gx, gy, dir)) {
            found.insert(std::pair{nx, ny});
          }
          rows[ny].erase(nx);
          cols[nx].erase(ny);
        }
        lines[gy][gx] = 'X';
        ++gx;
      } else {
        dir = down;
      }
    } else if (dir == down) {
      int ny = gy + 1;
      int nx = gx;
      if (ny == Ny)
        break;
      if (lines[ny][gx] != '#') {
        if (lines[ny][nx] == '.') {
          rows[ny].insert(nx);
          cols[nx].insert(ny);
          if (contains_loop(rows, cols, gx, gy, dir)) {
            found.insert(std::pair{nx, ny});
          }
          rows[ny].erase(nx);
          cols[nx].erase(ny);
        }
        lines[gy][gx] = 'X';
        ++gy;
      } else {
        dir = left;
      }
    } else {
      int ny = gy;
      int nx = gx - 1;
      if (nx < 0)
        break;
      if (lines[gy][gx - 1] != '#') {
        if (lines[ny][nx] == '.') {
          rows[ny].insert(nx);
          cols[nx].insert(ny);
          if (contains_loop(rows, cols, gx, gy, dir)) {
            found.insert(std::pair{nx, ny});
          }
          rows[ny].erase(nx);
          cols[nx].erase(ny);
        }
        lines[gy][gx] = 'X';
        --gx;
      } else {
        dir = up;
      }
    }
  }

  int res = found.size();
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 6);
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
