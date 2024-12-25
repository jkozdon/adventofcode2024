#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <ranges>
#include <vector>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <string>
#include <unordered_map>

namespace day21
{

void part1(const std::string &input, const bool test)
{
  std::unordered_map<char, std::pair<int, int>> num_map;
  num_map['7'] = {0, 3};
  num_map['8'] = {1, 3};
  num_map['9'] = {2, 3};
  num_map['4'] = {0, 2};
  num_map['5'] = {1, 2};
  num_map['6'] = {2, 2};
  num_map['1'] = {0, 1};
  num_map['2'] = {1, 1};
  num_map['3'] = {2, 1};
  num_map['0'] = {1, 0};
  num_map['A'] = {2, 0};
  auto num_button_path = [&](char start, char end) {
    auto c = num_map[start];
    auto t = num_map[end];
    std::vector<std::string> moves;
    {
      std::string move;
      while (c.first < t.first) {
        ++c.first;
        move.push_back('>');
      }
      while (c.second < t.second) {
        ++c.second;
        move.push_back('^');
      }
      while (t.first < c.first) {
        --c.first;
        move.push_back('<');
      }
      while (t.second < c.second) {
        --c.second;
        move.push_back('v');
      }
      move.push_back('A');
      moves.push_back(move);
    }
    c = num_map[start];
    t = num_map[end];
    if (c.first != t.first && c.second != t.second) {
      if (std::pair(c.first, t.second) != std::pair(0, 0) &&
          std::pair(t.first, c.second) != std::pair(0, 0)) {
        std::string move;
        while (t.first < c.first) {
          --c.first;
          move.push_back('<');
        }
        while (t.second < c.second) {
          --c.second;
          move.push_back('v');
        }
        while (c.first < t.first) {
          ++c.first;
          move.push_back('>');
        }
        while (c.second < t.second) {
          ++c.second;
          move.push_back('^');
        }
        move.push_back('A');
        moves.push_back(move);
      }
    }
    return moves;
  };

  std::unordered_map<char, std::pair<int, int>> move_map;
  move_map['^'] = {1, 1};
  move_map['A'] = {2, 1};
  move_map['<'] = {0, 0};
  move_map['v'] = {1, 0};
  move_map['>'] = {2, 0};
  auto move_button_path = [&](char start, char end) {
    auto c = move_map[start];
    auto t = move_map[end];
    std::vector<std::string> moves;
    {
      std::string move;
      while (t.second < c.second) {
        --c.second;
        move.push_back('v');
      }
      while (c.first < t.first) {
        ++c.first;
        move.push_back('>');
      }
      while (c.second < t.second) {
        ++c.second;
        move.push_back('^');
      }
      while (t.first < c.first) {
        --c.first;
        move.push_back('<');
      }
      move.push_back('A');
      moves.push_back(move);
    }
    c = move_map[start];
    t = move_map[end];
    if (c.first != t.first && c.second != t.second) {
      if (std::pair(c.first, t.second) != std::pair(0, 1) &&
          std::pair(t.first, c.second) != std::pair(0, 1)) {
        std::string move;
        while (t.first < c.first) {
          --c.first;
          move.push_back('<');
        }
        while (c.second < t.second) {
          ++c.second;
          move.push_back('^');
        }
        while (c.first < t.first) {
          ++c.first;
          move.push_back('>');
        }
        while (t.second < c.second) {
          --c.second;
          move.push_back('v');
        }
        move.push_back('A');
        moves.push_back(move);
      }
    }
    return moves;
  };
  auto move_path = [&](std::string code) {
    std::string moves;
    char start = 'A';
    for (int i = 0; i < code.size(); ++i) {
      auto moves = move_button_path(start, code[i]);
      start = code[i];
    }
    return moves;
  };
  auto num_path = [&](std::string l1_code) {
    char l1_start = 'A';
    char last = 'A';
    uint64_t res{0};
    for (int l1_i = 0; l1_i < l1_code.size(); ++l1_i) {
      auto l1_moves = num_button_path(l1_start, l1_code[l1_i]);
      l1_start = l1_code[l1_i];

      char l2_start = 'A';
      std::vector<uint64_t> l2_res;
      for (auto l2_code : l1_moves) {
        uint64_t res{0};
        for (int l2_i = 0; l2_i < l2_code.size(); ++l2_i) {
          auto l2_moves = move_button_path(l2_start, l2_code[l2_i]);
          l2_start = l2_code[l2_i];

          char l3_start = 'A';
          std::vector<uint64_t> l3_res;
          for (auto l3_code : l2_moves) {
            uint64_t res{0};
            for (int l3_i = 0; l3_i < l3_code.size(); ++l3_i) {
              auto l3_moves = move_button_path(l3_start, l3_code[l3_i]);
              l3_start = l3_code[l3_i];
              res += std::transform_reduce(
                  l3_moves.begin(), l3_moves.end(), UINT64_MAX,
                  [](auto a, auto b) { return a < b ? a : b; },
                  [](auto x) { return x.size(); });
            }
            l3_res.push_back(res);
          }
          res += std::reduce(l3_res.begin(), l3_res.end(), UINT64_MAX,
                             [](auto a, auto b) { return a < b ? a : b; });
        }
        l2_res.push_back(res);
      }
      res += std::reduce(l2_res.begin(), l2_res.end(), UINT64_MAX,
                         [](auto a, auto b) { return a < b ? a : b; });
    }
    return res;
  };

  uint64_t res = 0;
  auto lines = input | std::ranges::views::split('\n');
  for (auto view_line : lines) {
    if (view_line.empty())
      continue;
    std::string line = std::ranges::to<std::string>(view_line);
    res += std::atoi(line.c_str()) * num_path(line);
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 126384);
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
  auto input = read_input(base_path, 21, test);
  fmt::println("Day 21:");
  part1(input, test);
  part2(input, test);
}

} // namespace day21
