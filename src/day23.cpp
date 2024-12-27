#include <ranges>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"

namespace day23
{

void part1(const std::string &input, const bool test)
{
  auto lines = input | std::ranges::views::split('\n');
  std::unordered_map<std::string, uint64_t> name_to_ind;
  std::unordered_map<uint64_t, std::string> ind_to_name;
  std::unordered_map<uint64_t, std::unordered_set<uint64_t>> edges;
  std::unordered_set<uint64_t> tnodes;
  uint64_t next_ind{0};
  for (auto line : lines) {
    if (line.empty()) {
      continue;
    }
    std::string node_a = {line[0], line[1]};
    if (!name_to_ind.contains(node_a)) {
      ind_to_name[next_ind] = node_a;
      name_to_ind[node_a] = next_ind++;
    }
    auto ind_a = name_to_ind[node_a];

    std::string node_b = {line[3], line[4]};
    if (!name_to_ind.contains(node_b)) {
      ind_to_name[next_ind] = node_b;
      name_to_ind[node_b] = next_ind++;
    }
    auto ind_b = name_to_ind[node_b];
    edges[ind_a].insert(ind_b);
    edges[ind_b].insert(ind_a);
    if (node_a[0] == 't') {
      tnodes.insert(ind_a);
    }
    if (node_b[0] == 't') {
      tnodes.insert(ind_b);
    }
  }

  // count triangles
  std::unordered_set<uint64_t> seen;
  uint64_t res = 0;
  for (auto n : tnodes) {
    auto end = edges[n].end();
    seen.insert(n);
    for (auto nbrs = edges[n].begin(); nbrs != end; ++nbrs) {
      auto n_nbrs = nbrs;
      n_nbrs++;
      auto i = *nbrs;
      auto &i_edges = edges[i];
      if (seen.contains(i)) {
        continue;
      }
      for (; n_nbrs != end; ++n_nbrs) {
        auto j = *n_nbrs;
        if (seen.contains(j)) {
          continue;
        }
        if (i_edges.contains(j)) {
          ++res;
        }
      }
    }
  }
  fmt::print("  Part a: {}\n", res);
  if (test) {
    assert(res == 7);
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
  auto input = read_input(base_path, 23, test);
  fmt::println("Day 23:");
  part1(input, test);
  part2(input, test);
}

} // namespace day23
