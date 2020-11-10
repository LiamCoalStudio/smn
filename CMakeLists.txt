cmake_minimum_required(VERSION 3.17)
project(smn)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(src)
include_directories(src/elements)
include_directories(src/functions)
include_directories(src/module/std)
include_directories(src/module/std/elements/io)
include_directories(src/module/std/elements/math)
include_directories(src/generators)

add_compile_options(-DTESTING)

link_libraries(dl)
add_library(smnl STATIC src/elements/exec_function_element.cpp src/elements/exec_function_element.h src/elements/function_element.cpp src/elements/function_element.h src/elements/include_element.cpp src/elements/include_element.h src/elements/module_element.cpp src/elements/module_element.h src/elements/set_variable_element.cpp src/elements/set_variable_element.h src/elements/use_element.cpp src/elements/use_element.h src/functions/function.cpp src/functions/function_mgmt.cpp src/functions/functions.h src/elements.cpp src/elements.h src/language_element.h src/main.cpp src/module.cpp src/module.h src/parser.cpp src/simon.h src/str.cpp src/str.h src/use.cpp src/use.h optionparser.h src/languages.h src/generators/generator.cpp src/generators/generator.h src/generators/cpp_generator.cpp)
link_libraries(smnl dl)
add_executable(smn src/main.cpp)
add_library(std SHARED src/module/std/elements/io/print_element.cpp src/module/std/elements/io/print_element.h src/module/std/elements/io/println_element.cpp src/module/std/elements/io/println_element.h src/module/std/elements/math/add_element.cpp src/module/std/elements/math/add_element.h src/module/std/elements/math/divide_element.cpp src/module/std/elements/math/divide_element.h src/module/std/elements/math/modulus_element.cpp src/module/std/elements/math/modulus_element.h src/module/std/elements/math/multiply_element.cpp src/module/std/elements/math/multiply_element.h src/module/std/elements/math/subtract_element.cpp src/module/std/elements/math/subtract_element.h src/module/std/std.cpp src/module/std/str.cpp src/module/std/str.h)

install(TARGETS std DESTINATION ${CMAKE_SOURCE_DIR})
