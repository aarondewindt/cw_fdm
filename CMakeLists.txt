cmake_minimum_required(VERSION 3.16)
project(cw_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-fPIC")

set(BOOST_ENABLE_CMAKE 1)

add_subdirectory(lib/Catch2)
add_subdirectory(lib/eigen)
add_subdirectory(lib/span)
add_subdirectory(lib/fmt)

#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)
#find_package(Boost 1.67 REQUIRED COMPONENTS filesystem)
#message(STATUS "Boost version: ${Boost_VERSION}")

add_library(cw_sim SHARED
    src/variables_database.cpp
    src/cw.cpp
    src/exception.cpp

    include/variables_database.hpp
    include/cw.hpp
    include/exception.hpp
    include/mutable_token.hpp
    include/immutable_token.hpp
    include/variable.hpp
    include/module.h
    include/handler.h
#    include/continuous_handler.hpp
#    include/discreet_handler.hpp
#    src/discreet_handler.cpp
#    src/continuous_handler.cpp
        )

target_include_directories(cw_sim PUBLIC include)
#target_include_directories(cw_sim PUBLIC lib/odeint/include)
target_link_libraries (cw_sim Eigen3::Eigen)
target_link_libraries (cw_sim span)
target_link_libraries(cw_sim fmt)
#target_link_libraries(cw_sim Boost::headers)

add_subdirectory(tests)
add_subdirectory(spike)
