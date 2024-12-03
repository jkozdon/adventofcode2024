cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(AdventOfCode2023 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS On)

include(FetchContent)

FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 10.1.1
)

FetchContent_MakeAvailable(fmt)

add_executable(advent
	src/driver.cpp
	src/day01.cpp
	src/day02.cpp
	src/day03.cpp
	src/day04.cpp
	src/day05.cpp
	src/day06.cpp
	src/day07.cpp
	src/day08.cpp
	src/day09.cpp
	src/day10.cpp
	src/day11.cpp
	src/day12.cpp
	src/day13.cpp
	src/day14.cpp
	src/day15.cpp
	src/day16.cpp
	src/day17.cpp
	src/day18.cpp
	src/day19.cpp
	src/day20.cpp
	src/day21.cpp
	src/day22.cpp
	src/day23.cpp
	src/day24.cpp
	src/day25.cpp
)

target_link_libraries(advent
  PRIVATE 
    fmt::fmt 
)
