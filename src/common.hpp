#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include <fmt/core.h>

namespace day01
{
void run(const std::string &base_path, const bool test);
} // namespace day01

namespace day02
{
void run(const std::string &base_path, const bool test);
} // namespace day02

inline std::string read_input(const std::string &base_path, int day, bool test)
{
  std::string input_file = base_path + "/day" + (day < 10 ? "0" : "") +
                           std::to_string(day) +
                           (test ? "/test.txt" : "/input.txt");

  auto fs = std::ifstream(input_file);
  if (!fs.is_open()) {
    fmt::print("Error: cannot open input file: {}\n", input_file);
    exit(1);
  }

  auto buffer = std::stringstream{};
  buffer << fs.rdbuf();
  fs.close();
  return buffer.str();
}
