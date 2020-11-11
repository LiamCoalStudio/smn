cmake_minimum_required(VERSION 3.16)

project(smn)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)
include_directories(src/generators)

if(${TESTING})
    add_compile_options(-DTESTING=true)
endif()

link_libraries(dl)
add_library(smnl STATIC src/main.cpp src/parser.cpp src/simon.h optionparser.h src/languages.h src/generators/generator.h src/generators/cpp_generator.cpp)
add_library(simondev src/simondev.h src/simondev.cpp)
link_libraries(smnl dl)
add_executable(smn src/main.cpp)

install(FILES ${CMAKE_SOURCE_DIR}/src/simondev.h DESTINATION /usr/include)
install(TARGETS simondev smnl DESTINATION /usr/lib)
install(TARGETS smn DESTINATION /usr/bin)

enable_testing()

set(ALL_TESTS_GEN test_framework test_stack)

foreach(a ${ALL_TESTS_GEN})
    add_custom_command(OUTPUT tests/${a}.cpp COMMAND smn -g -o tests/${a}.cpp tests/${a}.cpp.smn COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests COMMAND cp tests/${a}.cpp ${CMAKE_BINARY_DIR}/tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endforeach()

link_libraries(simondev)

add_executable(test_framework tests/test_framework.cpp)
add_test(framework test_framework)

add_executable(test_stack tests/test_stack.cpp)
add_test(stack test_stack)
