cmake_minimum_required(VERSION 3.24)
project(bugs_life)

set(CMAKE_CXX_STANDARD 17)

add_executable(bugs_life main.cpp Bug.h Hopper.h Hopper.cpp Bug.cpp Crawler.h Crawler.cpp Board.h Board.cpp DiagonalBug.h DiagonalBug.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/Users/kevas/OneDrive/Desktop/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/Users/kevas/OneDrive/Desktop/include)
target_link_libraries(bugs_life sfml-system sfml-window sfml-graphics sfml-audio)