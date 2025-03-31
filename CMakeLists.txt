cmake_minimum_required(VERSION 3.10)
project(chip8)

set(CMAKE_C_STANDARD 99)

# Add source files
file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(chip8 ${SDL2_LIBRARIES})
