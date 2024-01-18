cmake_minimum_required(VERSION 3.12)

project(CppDemo)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)

# 添加可执行文件
add_executable(${PROJECT_NAME} main.cpp)

# 添加线程库
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
