# cmake 最低版本需求
cmake_minimum_required(VERSION 3.10.2)

# 工程名称
project(turing)

# EXECUTABLE_OUTPUT_PATH
# 设置
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set($ENV{PATH} ${PROJECT_SOURCE_DIR})
add_executable(turing src/main.cpp)