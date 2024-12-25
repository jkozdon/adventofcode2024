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
std::vector<std::string> num_button_path(char start, char end)
{
  std::unordered_map<char, std::pair<int, int>> num_map = {
      {'7', {0, 3}}, {'8', {1, 3}}, {'9', {2, 3}}, //
      {'4', {0, 2}}, {'5', {1, 2}}, {'6', {2, 2}}, //
      {'1', {0, 1}}, {'2', {1, 1}}, {'3', {2, 1}}, //
      {'0', {1, 0}}, {'A', {2, 0}}};
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

std::vector<std::string> move_button_path(char start, char end)
{
  std::unordered_map<char, std::pair<int, int>> move_map = {
      {'^', {1, 1}}, {'A', {2, 1}},                //
      {'<', {0, 0}}, {'v', {1, 0}}, {'>', {2, 0}}, //
  };

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

template <unsigned level> uint64_t move_path(std::vector<std::string> moves)
{
  char start = 'A';
  std::vector<uint64_t> vec_res;
  for (auto code : moves) {
    uint64_t res{0};
    for (int i = 0; i < code.size(); ++i) {
      uint64_t new_res{0};
      auto moves = move_button_path(start, code[i]);
      if constexpr (level > 1) {
        new_res = move_path<level - 1>(moves);
      } else {
        new_res = std::transform_reduce(
            moves.begin(), moves.end(), UINT64_MAX,
            [](auto a, auto b) { return a < b ? a : b; },
            [](auto x) { return x.size(); });
      }
      res += new_res;
      start = code[i];
    }
    vec_res.push_back(res);
  }
  return std::reduce(vec_res.begin(), vec_res.end(), UINT64_MAX,
                     [](auto a, auto b) { return a < b ? a : b; });
}

template <unsigned levels> uint64_t num_path(std::string code)
{
  char start = 'A';
  char last = 'A';
  uint64_t res{0};
  for (int i = 0; i < code.size(); ++i) {
    auto moves = num_button_path(start, code[i]);
    start = code[i];
    res += move_path<levels>(moves);
  }
  return res;
};

void part1(const std::string &input, const bool test)
{
  uint64_t res = 0;
  auto lines = input | std::ranges::views::split('\n');
  for (auto view_line : lines) {
    if (view_line.empty())
      continue;
    std::string line = std::ranges::to<std::string>(view_line);
    res += std::atoi(line.c_str()) * num_path<2>(line);
  }

  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 126384);
  }
}

void part2(const std::string &input, const bool test)
{
  uint64_t res = 0;
  fmt::print("  Part b: {}\n", res);
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 21, test);
  fmt::println("Day 21:");
  part1(input, test);
  part2(input, test);
}

} // namespace day21
