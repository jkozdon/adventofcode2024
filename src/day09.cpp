#include <deque>
#include <list>
#include <vector>
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

struct space_part {
  int fid;
  uint64_t size;
};

void part2(const std::string &input, const bool test)
{
  std::list<space_part> parts;
  std::vector<space_part> files;
  int fid = 0;
  for (auto c = input.begin(); c != input.end() && *c != '\n'; ++c) {
    parts.push_back({fid, (uint64_t)(*c - '0')});
    files.push_back({fid, (uint64_t)(*c - '0')});
    ++fid;
    ++c;
    if (c == input.end() || *c == '\n') {
      break;
    }
    parts.push_back({-1, (uint64_t)(*c - '0')});
  }

  for (auto rit = files.rbegin(); rit != files.rend(); ++rit) {
    auto n = (*rit);
    for (auto pit = parts.begin(); pit != parts.end(); ++pit) {
      auto &p = *pit;
      if (p.fid == n.fid) {
        break;
      }
      if (p.fid == -1 && p.size >= n.size) {
        auto size = p.size - n.size;
        if (p.size == n.size) {
          (*pit).fid = n.fid;
        } else {
          (*pit).size -= n.size;
          parts.insert(pit, n);
        }
        auto prev = pit++;
        for (; (*pit).fid != n.fid; prev = pit++)
          ;
        (*pit).fid = -1;
        if ((*prev).fid == -1) {
          (*pit).size += (*prev).size;
          parts.erase(prev);
        }
        auto next = pit;
        next++;
        if (next != parts.end() && (*next).fid == -1) {
          (*pit).size += (*next).size;
          parts.erase(next);
        }
        break;
      }
    }
  }

  int c = 0;
  uint64_t res = 0;
  for (auto n : parts) {
    if (n.fid == -1) {
      c += n.size;
      continue;
    }
    for (int i = 0; i < n.size; ++i, ++c) {
      res += n.fid * c;
    }
  }

  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == 2858L);
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
