cmake_minimum_required(VERSION 3.16)

project(LegdropLegends)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
)

add_executable(LegdropLegends ${SOURCES})

target_include_directories(LegdropLegends PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(LegdropLegends PRIVATE
    raylib
    tinyxml2::tinyxml2
)