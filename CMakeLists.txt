cmake_minimum_required(VERSION 3.16)
project(simon)

set(CMAKE_CXX_STANDARD 20)
include_directories(.)

if (SIMON_TESTING_MODE)
    add_compile_options(-Dmodule_path=\"cmake-build-testing\" -DTESTING=true)
endif ()

add_executable(smn src/main.cpp src/language_element.h src/simon.h src/elements.cpp src/elements.h src/str.cpp src/str.h src/elements/set_variable_element.cpp src/elements/set_variable_element.h  src/parser.cpp src/use.cpp src/use.h src/elements/use_element.cpp src/elements/use_element.h src/elements/module_element.cpp src/elements/module_element.h src/module.cpp src/module.h src/elements/function_element.cpp src/elements/function_element.h src/functions/functions.h src/functions/function.cpp src/functions/function_mgmt.cpp src/elements/include_element.cpp src/elements/include_element.h src/elements/exec_function_element.cpp src/elements/exec_function_element.h)
add_library(std SHARED src/module/std/std.cpp src/module/std/elements/io/println_element.cpp src/module/std/elements/io/println_element.h src/module/std/elements/io/print_element.cpp src/module/std/elements/io/print_element.h src/module/std/str.cpp src/module/std/str.h src/module/std/elements/math/add_element.cpp src/module/std/elements/math/add_element.h src/module/std/elements/math/subtract_element.cpp src/module/std/elements/math/subtract_element.h src/module/std/elements/math/multiply_element.cpp src/module/std/elements/math/multiply_element.h src/module/std/elements/math/divide_element.cpp src/module/std/elements/math/divide_element.h src/module/std/elements/math/modulus_element.cpp src/module/std/elements/math/modulus_element.h)
target_link_libraries(smn dl)

install(TARGETS smn DESTINATION /usr/bin)
install(TARGETS std DESTINATION /usr/share/simon/modules)
