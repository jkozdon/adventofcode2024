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

  day01::run(base_path, test);
  day02::run(base_path, test);
  day03::run(base_path, test);
  day04::run(base_path, test);
  day05::run(base_path, test);
  day06::run(base_path, test);
  day07::run(base_path, test);
  day08::run(base_path, test);
  day09::run(base_path, test);
  day10::run(base_path, test);
  day11::run(base_path, test);
  day12::run(base_path, test);
  day13::run(base_path, test);
  day14::run(base_path, test);
  day15::run(base_path, test);
  day16::run(base_path, test);
  day17::run(base_path, test);
  day18::run(base_path, test);
  day19::run(base_path, test);
  day20::run(base_path, test);
  day21::run(base_path, test);
  day22::run(base_path, test);
  day23::run(base_path, test);
  day24::run(base_path, test);
  day25::run(base_path, test);
}
