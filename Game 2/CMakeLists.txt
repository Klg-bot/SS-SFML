cmake_minimum_required(VERSION 3.0.0)
project(Game2 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Game2 main.cpp Balls.cpp Player.cpp Game.cpp)
target_link_libraries(Game2 sfml-graphics sfml-system sfml-window)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.5.1_2/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics system window REQUIRED)

