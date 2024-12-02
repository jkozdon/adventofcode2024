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
}
