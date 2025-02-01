cmake_minimum_required(VERSION 3.10)
project(srflp)

if (NOT CMAKE_CXX_COMPILER MATCHES "clang")
	message(FATAL_ERROR "Please use Clang as the compiler (e.g., set CMAKE_CXX_COMPILER to clang++)")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP REQUIRED)
message(STATUS "OpenMP version found: ${OpenMP_CXX_VERSION}")

include_directories(src)
link_libraries(OpenMP::OpenMP_CXX)

add_subdirectory(src)
add_subdirectory(test)
