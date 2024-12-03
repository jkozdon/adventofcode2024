#pragma once

#include <fstream>
#include <sstream>
#include <string>

#include <fmt/core.h>

#define MAKE_DAY(NUM) \
namespace day##NUM \
{ \
void run(const std::string &base_path, const bool test); \
}

MAKE_DAY(01)
MAKE_DAY(02)
MAKE_DAY(03)
MAKE_DAY(04)
MAKE_DAY(05)
MAKE_DAY(06)
MAKE_DAY(07)
MAKE_DAY(08)
MAKE_DAY(09)
MAKE_DAY(10)
MAKE_DAY(11)
MAKE_DAY(12)
MAKE_DAY(13)
MAKE_DAY(14)
MAKE_DAY(15)
MAKE_DAY(16)
MAKE_DAY(17)
MAKE_DAY(18)
MAKE_DAY(19)
MAKE_DAY(20)
MAKE_DAY(21)
MAKE_DAY(22)
MAKE_DAY(23)
MAKE_DAY(24)
MAKE_DAY(25)

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
