#include <deque>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

namespace day09
{

void part1(const std::string &input, const bool test)
{
  std::deque<int> disk;
  for (auto c : input) {
    if (c >= '0' && c <= '9')
      disk.push_back(c - '0');
  }
  // last entry is a blank
  if (disk.size() % 2 == 0)
    disk.pop_back();
  uint64_t res = 0;
  uint64_t place = 0;
  auto f_fid = 0;
  auto l_fid = (disk.size()) / 2;
  while (!disk.empty()) {
    auto v = disk.front();
    disk.pop_front();
    for (int i = 0; i < v; ++i, ++place) {
      res += place * f_fid;
    }
    ++f_fid;
    if (disk.empty())
      break;
    auto e = disk.front();
    disk.pop_front();

    while (e > 0) {
      auto l = disk.back();
      disk.pop_back();
      if (l == 0) {
        --l_fid;
        if (disk.empty()) {
          break;
        }
        disk.pop_back();
        continue;
      }
      res += l_fid * place;
      ++place;
      --l;
      --e;
      disk.push_back(l);
    }
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 1928L);
  }
}

void part2(const std::string &input, const bool test)
{
  uint64_t res = 0;
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 0);
  }
}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 9, test);
  fmt::println("Day 09:");
  part1(input, test);
  part2(input, test);
}

} // namespace day09
