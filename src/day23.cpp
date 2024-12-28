#include <ranges>
#include <set>
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

// algorithm BronKerbosch1(R, P, X) is
//     if P and X are both empty then
//         report R as a maximal clique
//     for each vertex v in P do
//         BronKerbosch1(R ⋃ {v}, P ⋂ N(v), X ⋂ N(v))
//           P := P \ {v}
//           X := X ⋃ {v}
void bron_kerbosch(
    std::unordered_map<uint64_t, std::unordered_set<uint64_t>> &edges, //
    std::unordered_set<uint64_t> R,                                    //
    std::unordered_set<uint64_t> P,                                    //
    std::unordered_set<uint64_t> X, std::unordered_set<uint64_t> &max_clique)
{
  if (max_clique.size() >= R.size() + P.size()) {
    return;
  }
  if (P.empty() && X.empty()) {
    if (max_clique.size() < R.size()) {
      max_clique = R;
    }
    return;
  }
  while (!P.empty()) {
    auto v = *(P.begin());
    R.insert(v);
    std::unordered_set<uint64_t> new_P;
    std::unordered_set<uint64_t> new_X;
    for (auto w : edges[v]) {
      if (P.contains(w)) {
        new_P.insert(w);
      }
      if (X.contains(w)) {
        new_X.insert(w);
      }
    }
    bron_kerbosch(edges, R, new_P, new_X, max_clique);
    R.erase(v);
    P.erase(v);
    X.insert(v);
  }
}

void part2(const std::string &input, const bool test)
{
  auto lines = input | std::ranges::views::split('\n');
  std::unordered_map<std::string, uint64_t> name_to_ind;
  std::unordered_map<uint64_t, std::string> ind_to_name;
  std::unordered_map<uint64_t, std::unordered_set<uint64_t>> edges;
  std::unordered_set<uint64_t> node_list;
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
    node_list.insert(ind_a);
    node_list.insert(ind_b);
  }

  // cliques
  std::unordered_set<uint64_t> max_clique;
  bron_kerbosch(edges, {}, node_list, {}, max_clique);
  std::set<std::string> clique;
  for (auto v : max_clique) {
    clique.insert(ind_to_name[v]);
  }
  auto citer = clique.begin();
  std::string res = *citer;
  for (++citer; citer != clique.end(); ++citer) {
    res.append(",");
    res.append(*citer);
  }
  fmt::print("  Part b: {}\n", res);
  if (test) {
    assert(res == "co,de,ka,ta");
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
