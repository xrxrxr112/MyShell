# 在项目的根目录下的 CMakeLists.txt 文件
cmake_minimum_required(VERSION 3.10)
project(MyShell)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译器标志，确保使用 C++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 包含 src 目录下的头文件
include_directories(src)

set(SOURCE_FILES src/MyShell.cpp)

# 添加可执行文件
add_executable(MyShell ${SOURCE_FILES})
