cmake_minimum_required(VERSION 3.9)

project("osie")

set(CMAKE_CXX_STANDARD 17)

find_package(PNG REQUIRED)

add_executable(osie)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(osie PRIVATE PNG::PNG)
