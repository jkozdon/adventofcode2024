#include "common.hpp"

namespace day01
{

void part1(const std::string &input, const bool test) {}

void part2(const std::string &input, const bool test) {}

void run(const std::string &base_path, const bool test)
{
  auto input = read_input(base_path, 1, test);
  part1(input, test);
  part2(input, test);
}

} // namespace day01
