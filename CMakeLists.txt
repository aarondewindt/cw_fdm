cmake_minimum_required(VERSION 3.16)
project(cw_sim)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-fPIC")

add_subdirectory(lib/Catch2)
add_subdirectory(lib/eigen)
add_subdirectory(lib/span)
add_subdirectory(lib/fmt)
add_subdirectory(tests)

add_library(cw_sim SHARED
        src/variables_database.cpp
        src/cw.cpp
        src/exception.cpp

        include/variables_database.hpp
        include/cw.hpp
        include/exception.hpp
        include/mutable_token.hpp
        include/immutable_token.hpp
        include/variable.hpp)

target_include_directories(cw_sim PUBLIC include)
target_link_libraries (cw_sim Eigen3::Eigen)
target_link_libraries (cw_sim span)
target_link_libraries(cw_sim fmt)
