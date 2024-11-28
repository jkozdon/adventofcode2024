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
	)
target_link_libraries(advent
  PRIVATE 
    fmt::fmt 
)

