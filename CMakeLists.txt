cmake_minimum_required(VERSION 3.20)

project(LegdropLegends)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/states/*.cpp
    src/objects/*.cpp
    src/core/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    raylib
)