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
add_executable(test_basics tests/test_basics.smn)
add_test(TestBasics test_basics)
