cmake_minimum_required(VERSION 3.30)
project(TinyEngine)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    add_compile_options(/wd4819)  #忽略保存为unicode警告
endif ()

include(CMakeLists.txt.glfw)
include_directories("depends")

add_executable(TinyEngine ${glfw_sources} example/main.cpp)

