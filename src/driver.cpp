#include <getopt.h>

#include "common.hpp"

void usage(const char *progname)
{
  fmt::print(stderr, "usage: {} -p <input directory> [-d <day>] [-t]\n",
             progname);
}

int main(int argc, char *argv[])
{
  int opt;
  int day = 0;
  bool test = false;
  std::string base_path = "";
  while ((opt = getopt(argc, argv, "p:d:t")) != -1) {
    switch (opt) {
    case 'd':
      day = std::stoi(optarg);
      break;
    case 't':
      test = true;
      break;
    case 'p':
      base_path = optarg;
      break;
    default:
      usage(argv[0]);
      return 1;
    }
  }

  if (base_path.empty()) {
    usage(argv[0]);
    return 1;
  }

  if (day == 0 || day == 1)
    day01::run(base_path, test);
  if (day == 0 || day == 2)
    day02::run(base_path, test);
  if (day == 0 || day == 3)
    day03::run(base_path, test);
  if (day == 0 || day == 4)
    day04::run(base_path, test);
  if (day == 0 || day == 5)
    day05::run(base_path, test);
  if (day == 0 || day == 6)
    day06::run(base_path, test);
  if (day == 0 || day == 7)
    day07::run(base_path, test);
  if (day == 0 || day == 8)
    day08::run(base_path, test);
  if (day == 0 || day == 9)
    day09::run(base_path, test);
  if (day == 0 || day == 10)
    day10::run(base_path, test);
  if (day == 0 || day == 11)
    day11::run(base_path, test);
  if (day == 0 || day == 12)
    day12::run(base_path, test);
  if (day == 0 || day == 13)
    day13::run(base_path, test);
  if (day == 0 || day == 14)
    day14::run(base_path, test);
  if (day == 0 || day == 15)
    day15::run(base_path, test);
  if (day == 0 || day == 16)
    day16::run(base_path, test);
  if (day == 0 || day == 17)
    day17::run(base_path, test);
  if (day == 0 || day == 18)
    day18::run(base_path, test);
  if (day == 0 || day == 19)
    day19::run(base_path, test);
  if (day == 0 || day == 20)
    day20::run(base_path, test);
  if (day == 0 || day == 21)
    day21::run(base_path, test);
  if (day == 0 || day == 22)
    day22::run(base_path, test);
  if (day == 0 || day == 23)
    day23::run(base_path, test);
  if (day == 0 || day == 24)
    day24::run(base_path, test);
  if (day == 0 || day == 25)
    day25::run(base_path, test);
}
