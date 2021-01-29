cmake_minimum_required(VERSION 3.0)

project(smn CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(src)
include_directories(src/generators)

if (${TESTING})
    add_compile_options(-DTESTING=true)
endif ()

link_libraries(dl)
add_compile_definitions(PRIVATE VERSION=\"0.4.1\")
add_library(smnl STATIC src/main.cpp src/parser.cpp src/simon.h optionparser.h src/languages.h src/generators/generator.h src/generators/cpp_generator.cpp src/generators/c_generator.cpp src/generators/generator.cpp)
add_library(simondevcxx src/simondev/cxx/simondevcxx.h src/simondev/cxx/simondevcxx.cpp)
add_library(simondevc src/simondev/c/simondevc.h src/simondev/c/simondevc.c)
link_libraries(smnl dl)
add_executable(smn src/main.cpp)
add_dependencies(smn simondevcxx simondevc)

install(
        FILES
        ${CMAKE_SOURCE_DIR}/src/simondev/cxx/simondevcxx.h
        ${CMAKE_SOURCE_DIR}/src/simondev/c/simondevc.h
        DESTINATION /usr/include
)
install(TARGETS simondevcxx simondevc smnl DESTINATION /usr/lib)
install(TARGETS smn DESTINATION /usr/bin)

enable_testing()

set(ALL_TESTS_CPP test_framework test_stack)
set(ALL_TESTS_C test_c_framework test_c_stack)

foreach (a ${ALL_TESTS_CPP})
    add_custom_command(OUTPUT tests/${a}.cpp COMMAND smn -g -o tests/${a}.cpp tests/${a}.cpp.smn COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests COMMAND cp tests/${a}.cpp ${CMAKE_BINARY_DIR}/tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach ()

foreach (a ${ALL_TESTS_C})
    add_custom_command(OUTPUT tests/${a}.c COMMAND smn -g -o tests/${a}.c tests/${a}.c.smn COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests COMMAND cp tests/${a}.c ${CMAKE_BINARY_DIR}/tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach ()

add_executable(test_framework tests/test_framework.cpp)
target_link_libraries(test_framework simondevcxx)
add_test(framework test_framework)

add_executable(test_stack tests/test_stack.cpp)
target_link_libraries(test_stack simondevcxx)
add_test(stack test_stack)

add_executable(test_c_framework tests/test_c_framework.c)
target_link_libraries(test_c_framework simondevc)
add_test(c_framework test_c_framework)

add_executable(test_c_stack tests/test_c_stack.c)
target_link_libraries(test_c_stack simondevc)
add_test(c_stack test_c_stack)
