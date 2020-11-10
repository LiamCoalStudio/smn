cmake_minimum_required(VERSION 3.17)
project(smn)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(src)
include_directories(src/generators)

add_compile_options(-DTESTING)

link_libraries(dl)
add_library(smnl STATIC src/main.cpp src/parser.cpp src/simon.h src/str.cpp src/str.h optionparser.h src/languages.h src/generators/generator.cpp src/generators/generator.h src/generators/cpp_generator.cpp)
link_libraries(smnl dl)
add_executable(smn src/main.cpp)
