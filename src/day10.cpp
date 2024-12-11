#include <ranges>
#include <stack>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <ranges>

namespace day10
{

void part1(const std::string &input, const bool test)
{
  std::vector<uint8_t> topo;
  std::vector<int> starts;
  auto lines = input | std::ranges::views::split('\n');
  int Nx = 0;
  for (auto c : input) {
    if (c == '\n')
      break;
    ++Nx;
  }
  for (auto c : input) {
    if (c == '0')
      starts.push_back(topo.size());
    if ('0' <= c && c <= '9') {
      topo.push_back(c - '0');
    } else {
    }
  }
  auto Ny = topo.size() / Nx;
  auto coord2ind = [Nx](int x, int y) { return x + y * Nx; };
  auto ind2coord = [Nx](int s) { return std::pair{s % Nx, s / Nx}; };
  auto valid = [Nx, Ny](int x, int y) {
    return 0 <= x && x < Nx && 0 <= y && y < Ny;
  };
  int res = 0;
  for (auto s : starts) {
    std::stack<std::tuple<int, int, int>> nodes;
    std::unordered_set<int> found;
    auto [x, y] = ind2coord(s);
    nodes.push({x, y, 0});
    while (!nodes.empty()) {
      auto [x, y, p] = nodes.top();
      nodes.pop();
      ++p;
      auto v = topo[coord2ind(x, y)];
      auto maybe_add_next = [&](auto x, auto y) {
        if (valid(x, y) && v + 1 == topo[coord2ind(x, y)]) {
          nodes.push({x, y, 0});
        }
      };
      if (v == 9) {
        found.insert(coord2ind(x, y));
      } else if (p == 1) {
        nodes.push({x, y, p});
        maybe_add_next(x - 1, y);
      } else if (p == 2) {
        nodes.push({x, y, p});
        maybe_add_next(x + 1, y);
      } else if (p == 3) {
        nodes.push({x, y, p});
        maybe_add_next(x, y - 1);
      } else if (p == 4) {
        nodes.push({x, y, p});
        maybe_add_next(x, y + 1);
      }
    }
    res += found.size();
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 36);
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
  auto input = read_input(base_path, 10, test);
  fmt::println("Day 10:");
  part1(input, test);
  part2(input, test);
}

} // namespace day10
