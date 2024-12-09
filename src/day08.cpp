#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day08
{
struct hash_pair {
  size_t operator()(const std::pair<int, int> &p) const
  {
    return (size_t)(p.first + p.second * 1024);
  }
};

struct hash_tuple {
  size_t operator()(const std::tuple<char, int, int> &p) const
  {
    return (size_t)(std::get<0>(p) + 1024 * std::get<1>(p) +
                    1024 * 1024 * std::get<2>(p));
  }
};

void part1(const std::string &input, const bool test)
{
  int num_cols = 0;
  for (auto c : input) {
    if (c == '\n')
      break;
    ++num_cols;
  }
  int num_rows = input.size() / (num_cols + 1);

  auto lines = input | std::views::split('\n');

  int c_row = 0;
  std::unordered_map<int, std::unordered_set<std::pair<int, int>, hash_pair>>
      recvs;
  std::unordered_set<std::tuple<char, int, int>, hash_tuple> nodes;
  for (auto line = lines.begin(); line != lines.end(); ++line, ++c_row) {
    int c_col = 0;
    for (auto r : *line) {
      if (r != '.') {
        for (auto [n_row, n_col] : recvs[r]) {
          auto d_row = n_row - c_row;
          auto d_col = n_col - c_col;

          auto t_row = n_row + d_row;
          auto t_col = n_col + d_col;

          auto s_row = c_row - d_row;
          auto s_col = c_col - d_col;

          if (0 <= t_row && t_row < num_rows && //
              0 <= t_col && t_col < num_cols) {
            nodes.insert(std::tuple{'.', t_row, t_col});
          }

          if (0 <= s_row && s_row < num_rows && //
              0 <= s_col && s_col < num_cols) {
            nodes.insert(std::tuple{'.', s_row, s_col});
          }
        }
        recvs[r].insert(std::pair{c_row, c_col});
      }
      ++c_col;
    }
  }
  int res = nodes.size();
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 14);
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
  auto input = read_input(base_path, 8, test);
  fmt::println("Day 08:");
  part1(input, test);
  part2(input, test);
}

} // namespace day08
