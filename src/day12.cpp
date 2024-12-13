#include <unordered_set>
#include <vector>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day12
{

void part1(const std::string &input, const bool test)
{
  int Nx = 0;
  for (auto c : input) {
    if (c == '\n') {
      break;
    }
    ++Nx;
  }
  int Ny = input.size() / (Nx + 1);
  auto coord2ind = [Nx](int x, int y) { return x + y * Nx; };
  auto ind2coord = [Nx](int s) { return std::pair{s % Nx, s / Nx}; };
  auto valid = [Nx, Ny](int x, int y) {
    return 0 <= x && x < Nx && 0 <= y && y < Ny;
  };
  auto get_field = [Nx, Ny, &input, &valid](int i, int j) {
    return valid(i, j) ? input[i + j * (Nx + 1)] : '*';
  };

  int res = 0;
  std::vector<bool> visited(Nx * Ny);
  auto get_visited = [Nx, &visited, &valid](int i, int j) {
    return valid(i, j) ? visited[i + j * Nx] : false;
  };
  for (int j = 0; j < Ny; ++j) {
    for (int i = 0; i < Nx; ++i) {
      if (visited[i + j * Nx]) {
        continue;
      }
      std::unordered_set<int> seen;
      seen.insert(coord2ind(i, j));
      const char field = get_field(i, j);
      int perm = 0;
      int area = 0;
      while (!seen.empty()) {
        auto ind = *seen.begin();
        seen.erase(ind);
        visited[ind] = true;
        ++area;
        auto [x, y] = ind2coord(ind);
        auto handle_neighbor = [&field, &get_visited, &get_field, &perm,
                                &coord2ind, &seen](int x, int y) {
          if (get_field(x, y) != field) {
            ++perm;
          } else if (!get_visited(x, y)) {
            seen.insert(coord2ind(x, y));
          }
        };
        handle_neighbor(x, y + 1);
        handle_neighbor(x, y - 1);
        handle_neighbor(x + 1, y);
        handle_neighbor(x - 1, y);
      }
      res += perm * area;
    }
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 1930);
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
  auto input = read_input(base_path, 12, test);
  fmt::println("Day 12:");
  part1(input, test);
  part2(input, test);
}

} // namespace day12
