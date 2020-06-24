

add_executable(tests
        test_main.cpp
        test_factorial.cpp
        test_variables_and_tokens.cpp
        test_cw.cpp)

target_link_libraries(tests Catch2::Catch2)
target_link_libraries (tests Eigen3::Eigen)
target_link_libraries (tests span)
target_link_libraries(tests fmt)
target_link_libraries(tests cw_sim)

