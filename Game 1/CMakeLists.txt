cmake_minimum_required(VERSION 3.0.0)
project(Game1 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Game1 main.cpp Game.cpp)
target_link_libraries(Game1 sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(SFML_DIR "/opt/homebrew/Cellar/sfml/2.5.1_2/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)