cmake_minimum_required(VERSION 3.24)
project(Project3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project3 main.cpp board.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/SFML/include)
target_link_libraries(Project3 sfml-system sfml-window sfml-graphics sfml-audio)

