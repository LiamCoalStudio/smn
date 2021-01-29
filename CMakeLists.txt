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

link_libraries(smnl dl)
add_executable(smn src/main.cpp)

enable_testing()

set(ALL_TESTS_CPP test_framework test_stack)
#set(ALL_TESTS_C test_c_framework test_c_stack)
set(SIMONDEV_FILES ${CMAKE_SOURCE_DIR}/simondev/simondev.h ${CMAKE_SOURCE_DIR}/simondev/simon.cpp)

foreach (a ${SIMONDEV_FILES})
    add_custom_command(
            OUTPUT ${a}
            COMMAND smn -g -o ${a} ${a}.smn
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            MAIN_DEPENDENCY ${a}.smn
            DEPENDS smn
    )
endforeach ()

foreach (a ${ALL_TESTS_CPP})
    add_custom_command(
            OUTPUT tests/${a}.cpp
            COMMAND smn -g -o tests/${a}.cpp tests/${a}.cpp.smn
            COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests
            COMMAND cp tests/${a}.cpp ${CMAKE_BINARY_DIR}/tests
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            MAIN_DEPENDENCY tests/${a}.cpp.smn
            DEPENDS smn
    )
endforeach ()

#foreach (a ${ALL_TESTS_C})
#    add_custom_command(OUTPUT tests/${a}.c COMMAND smn -g -o tests/${a}.c tests/${a}.c.smn COMMAND mkdir -p ${CMAKE_BINARY_DIR}/tests COMMAND cp tests/${a}.c ${CMAKE_BINARY_DIR}/tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
#endforeach ()

add_library(simondev STATIC ${SIMONDEV_FILES})
target_include_directories(simondev PUBLIC ${CMAKE_SOURCE_DIR}/simondev)

add_executable(test_framework tests/test_framework.cpp)
target_link_libraries(test_framework simondev)
add_test(framework test_framework)

add_executable(test_stack tests/test_stack.cpp)
target_link_libraries(test_stack simondev)
add_test(stack test_stack)

#add_executable(test_c_framework tests/test_c_framework.c)
#target_link_libraries(test_c_framework simondevc)
#add_test(c_framework test_c_framework)
#
#add_executable(test_c_stack tests/test_c_stack.c)
#target_link_libraries(test_c_stack simondevc)
#add_test(c_stack test_c_stack)

install(
        FILES
        ${CMAKE_SOURCE_DIR}/simondev/simondev.h
        DESTINATION /usr/include
)
install(TARGETS simondev smnl DESTINATION /usr/lib)
install(TARGETS smn DESTINATION /usr/bin)
