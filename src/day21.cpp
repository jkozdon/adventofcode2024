#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <cstdlib>
#include <ranges>
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
  auto num_button_path = [&](char start, char end, char last) {
    auto c = num_map[start];
    auto t = num_map[end];
    std::string moves;
    while (c.first < t.first) {
      ++c.first;
      moves.push_back('>');
    }
    while (c.second < t.second) {
      ++c.second;
      moves.push_back('^');
    }
    while (t.first < c.first) {
      --c.first;
      moves.push_back('<');
    }
    while (t.second < c.second) {
      --c.second;
      moves.push_back('v');
    }
    moves.push_back('A');
    return moves;
  };
  auto num_path = [&](std::string code) {
    std::string moves;
    char start = 'A';
    char last = 'A';
    for (int i = 0; i < code.size(); ++i) {
      moves.append(num_button_path(start, code[i], last));
      start = code[i];
      last = moves[moves.size() - 1];
    }
    fmt::println("{}", moves);
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
    std::string moves;
    while (t.second < c.second) {
      --c.second;
      moves.push_back('v');
    }
    while (c.first < t.first) {
      ++c.first;
      moves.push_back('>');
    }
    while (c.second < t.second) {
      ++c.second;
      moves.push_back('^');
    }
    while (t.first < c.first) {
      --c.first;
      moves.push_back('<');
    }
    moves.push_back('A');
    return moves;
  };
  auto move_path = [&](std::string code) {
    std::string moves;
    char start = 'A';
    for (int i = 0; i < code.size(); ++i) {
      moves.append(move_button_path(start, code[i]));
      start = code[i];
    }
    fmt::println("{}", moves);
    return moves;
  };

  uint64_t res = 0;
  auto lines = input | std::ranges::views::split('\n');
  for (auto view_line : lines) {
    if (view_line.empty())
      continue;
    std::string line = std::ranges::to<std::string>(view_line);
    auto moves = move_path(move_path(num_path(line)));
    auto num = std::atoi(line.substr(0, 3).c_str());
    fmt::println("{} * {}", moves.size(), num);
    res += num * moves.size();
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
