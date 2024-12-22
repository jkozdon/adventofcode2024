#include <regex>
#include <cassert>
#include <cstdint>

#include "common.hpp"
#include "fmt/core.h"
#include <string>
#include <unordered_map>

namespace day17
{

void part1(const std::string &input, const bool test)
{
  std::regex regex_A(R"(Register A: (\d*))");
  std::smatch match_regA;
  std::regex_search(input, match_regA, regex_A);
  int A = std::atoi(match_regA[1].str().c_str());
  std::regex regex_B(R"(Register B: (\d*))");
  std::smatch match_regB;
  std::regex_search(input, match_regB, regex_B);
  int B = std::atoi(match_regB[1].str().c_str());
  std::regex regex_C(R"(Register C: (\d*))");
  std::smatch match_regC;
  std::regex_search(input, match_regC, regex_C);
  int C = std::atoi(match_regC[1].str().c_str());
  auto prog_ind = input.find(",") - 1;
  std::vector<int8_t> prog;
  for (auto c : input.substr(prog_ind)) {
    if ('0' <= c && c <= '9') {
      prog.push_back(c - '0');
    }
  }
  int pc = 0;
  auto combo = [&](int8_t op) {
    if (op == 4) {
      return A;
    } else if (op == 5) {
      return B;
    } else if (op == 6) {
      return C;
    } else if (op == 7) {
      fmt::println("Illegal op code 7");
    }
    return (int)op;
  };
  std::string out;
  while (pc < prog.size()) {
    auto in = prog[pc];
    auto op = prog[pc + 1];
    pc += 2;
    if (in == 0 || in == 6 || in == 7) { // adv,bdv,cdv
      auto num = A;
      auto den = 1 << combo(op);
      auto res = num / den;
      if (in == 0) {
        A = res;
      } else if (in == 6) {
        B = res;
      } else {
        C = res;
      }
    } else if (in == 1) { // bxl
      B = B ^ op;
    } else if (in == 2) { // bst
      B = combo(op) % 8;
    } else if (in == 3) { // jnz
      if (A != 0) {
        pc = op;
      }
    } else if (in == 4) { // bxc
      B = B ^ C;
    } else if (in == 5) { // out
      if (!out.empty()) {
        out.append(",");
      }
      out.append(std::to_string(combo(op) % 8));
    } else if (in > 8 || in < 0) {
      fmt::println("Illegal instruction!");
      return;
    }
  }
  fmt::print("  Part a: {}\n", out);
  if (test) {
    assert(out == "4,6,3,5,6,3,5,2,1,0");
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
  auto input = read_input(base_path, 17, test);
  fmt::println("Day 17:");
  part1(input, test);
  part2(input, test);
}

} // namespace day17
