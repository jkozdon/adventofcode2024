#include <cassert>

#include "common.hpp"
#include "fmt/core.h"
#include <iterator>
#include <queue>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>

namespace day18
{

void part1(const std::string &input, const bool test)
{
  int size = test ? 7 : 71;
  auto coords = input | std::ranges::views::split('\n');
  std::unordered_map<int, int> visited;
  for (auto coord : coords | std::ranges::views::take(test ? 12 : 1024)) {
    std::istringstream ss(std::ranges::to<std::string>(coord));
    int x, y;
    char comma;
    ss >> x >> comma >> y;
    visited[y * size + x] = -1;
  }
  std::queue<std::tuple<int, int, int>> next;
  visited[0] = 0;
  next.push({0, 0, 0});
  while (!visited.contains(size * size - 1)) {
    if (next.empty())
      break;
    auto [x, y, l] = next.front();
    next.pop();
#pragma unroll
    for (int dy = -1; dy < 2; ++dy) {
#pragma unroll
      for (int dx = -1; dx < 2; ++dx) {
        if (dy != 0 && dx != 0)
          continue;
        auto nx = x + dx;
        auto ny = y + dy;
        if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
          auto ind = ny * size + nx;
          if (!visited.contains(ind)) {
            next.push({nx, ny, l + 1});
            visited[ind] = l + 1;
          }
        }
      }
    }
  }
  int res = visited[size * size - 1];
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 22);
  }
}

void part2(const std::string &input, const bool test)
{
  int size = test ? 7 : 71;
  auto coords = input | std::ranges::views::split('\n');
  auto line_count = std::ranges::distance(coords);

  int bracket_a = 1;
  int bracket_b = line_count;
  while (bracket_a != bracket_b) {
    int bracket_mid = (bracket_a + bracket_b) / 2;
    std::unordered_map<int, int> visited;
    for (auto coord : coords | std::ranges::views::take(bracket_mid)) {
      std::istringstream ss(std::ranges::to<std::string>(coord));
      int x, y;
      char comma;
      ss >> x >> comma >> y;
      visited[y * size + x] = -1;
    }
    std::queue<std::tuple<int, int, int>> next;
    visited[0] = 0;
    next.push({0, 0, 0});
    while (!visited.contains(size * size - 1)) {
      if (next.empty())
        break;
      auto [x, y, l] = next.front();
      next.pop();
#pragma unroll
      for (int dy = -1; dy < 2; ++dy) {
#pragma unroll
        for (int dx = -1; dx < 2; ++dx) {
          if (dy != 0 && dx != 0)
            continue;
          auto nx = x + dx;
          auto ny = y + dy;
          if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
            auto ind = ny * size + nx;
            if (!visited.contains(ind)) {
              next.push({nx, ny, l + 1});
              visited[ind] = l + 1;
            }
          }
        }
      }
    }
    if (visited.contains(size * size - 1)) {
      bracket_a = bracket_mid + 1;
    } else {
      bracket_b = bracket_mid;
    }
  }
  auto coord = coords.begin();
  std::advance(coord, bracket_a - 1);
  auto res = std::ranges::to<std::string>(*coord);
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == "6,1");
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 18, test);
  fmt::println("Day 18:");
  part1(input, test);
  part2(input, test);
}

} // namespace day18
