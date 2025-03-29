cmake_minimum_required(VERSION 3.10)
project(chip8)

# Add source files
file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})
