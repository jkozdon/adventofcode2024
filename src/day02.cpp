#include <ranges>
#include <cassert>

#include "common.hpp"
#include "fmt/core.h"

namespace day02
{

void part1(const std::string &input, const bool test)
{
  auto lines = input | std::views::split('\n');
  int res = 0;
  for (auto line : lines) {
    if (line.empty()) {
      break;
    }
    int next{};
    int last{};
    std::istringstream ss(std::ranges::to<std::string>(line));
    ss >> last >> next;
    bool increasing = next > last;
    bool valid = true;
    do {
      auto delta = std::abs(last - next);
      valid =
          0 < delta && delta < 4 && (increasing ? next > last : next < last);
      last = next;
    } while (valid && ss >> next);
    res += valid;
  }
  fmt::println("  Part a: {}", res);
  if (test) {
    assert(res == 2);
  }
}

void part2(const std::string &input, const bool test)
{
  auto lines = input | std::views::split('\n');
  int res = 0;
  for (auto line : lines) {
    auto is_valid = [](int a, int b, int c) {
      int del_ab = b - a;
      int del_bc = c - b;
      return del_ab * del_bc > 0 && -4 < del_ab && del_ab < 4 && -4 < del_bc &&
             del_bc < 4;
    };
    if (line.empty()) {
      break;
    }
    int a{};
    int b{};
    int c{};
    std::istringstream ss(std::ranges::to<std::string>(line));
    // Grab the first three, and see if they are valid.
    ss >> a >> b >> c;
    bool dropped = false;
    // If the first three are not valid, check if adding the fourth helps
    if (!is_valid(a, b, c)) {
      int d{};
      ss >> d;
      dropped = true;
      if (is_valid(a, b, d)) {
        c = d;
      } else if (is_valid(a, c, d)) {
        b = c;
        c = d;
      } else {
        // Since keeping a isn't valid, drop a and let the do...while handle this case
        a = b;
        b = c;
        c = d;
      }
    }
    bool valid = true;
    do {
      valid = is_valid(a, b, c);
      if (!valid && !dropped) {
        int d{};
        // If we have at least more see if this one works
        // If there are no more, that drop c
        if (ss >> d) {
          dropped = true;
          if (is_valid(a, b, d)) {
            valid = true;
            c = d;
          } else if (is_valid(a, c, d)) {
            valid = true;
            b = c;
            c = d;
          }
        } else {
          valid = true;
        }
      }
      a = b;
      b = c;
    } while (valid && ss >> c);
    res += valid;
  }
  fmt::println("  Part b: {}", res);
  if (test) {
    assert(res == 4);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 2, test);
  fmt::println("Day 02:");
  part1(input, test);
  part2(input, test);
}

} // namespace day02
