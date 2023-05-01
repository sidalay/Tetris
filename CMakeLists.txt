cmake_minimum_required(VERSION 3.16)
project(tetris)

find_package(raylib QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
    FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

add_executable(${PROJECT_NAME}
  src/animations.cpp
  src/audio.cpp
  src/bag.cpp
  src/block.cpp
  src/controller.cpp
  src/enforcer.cpp
  src/game.cpp
  src/garbage.cpp
  src/handler.cpp
  src/lerp.cpp
  src/level.cpp
  src/main.cpp
  src/matrix.cpp
  src/play.cpp
  src/player.cpp
  src/randomizer.cpp
  src/score.cpp
  src/tetromino.cpp
  src/texture.cpp
  src/window.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE include ${raylib_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_options(${PROJECT_NAME} INTERFACE -Wall -Wextra -Wpedantic)

# file(COPY audio sprites DESTINATION ${CMAKE_BINARY_DIR})