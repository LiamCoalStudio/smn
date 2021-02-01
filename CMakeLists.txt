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

add_compile_definitions(PRIVATE VERSION=\"0.6.0\")
add_library(smnl STATIC src/main.cpp src/parser.cpp src/simon.h optionparser.h src/languages.h src/generators/generator.h src/generators/cpp_generator.cpp src/generators/c_generator.cpp src/generators/generator.cpp)

link_libraries(smnl dl)
add_executable(smn src/main.cpp)

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

add_library(simondev STATIC ${SIMONDEV_FILES})
target_include_directories(simondev PUBLIC ${CMAKE_SOURCE_DIR}/simondev)

install(
        FILES
        ${CMAKE_SOURCE_DIR}/simondev/simondev.h
        DESTINATION /usr/include
)
install(TARGETS simondev smnl DESTINATION /usr/lib)
install(TARGETS smn DESTINATION /usr/bin)
