//
// Created by adewindt on 3/14/20.
//

#include <typeinfo>
#include <iostream>

#include "catch2/catch.hpp"
#include "test_cw.hpp"
#include "fmt/core.h"

#include "Eigen/Dense"


namespace cw::testing {
    TEST_CASE( "Get type name" ) {
        const std::type_info& type_info = typeid(Eigen::MatrixXd);
        auto type_name = get_type_name(type_info);

        CHECK_THAT(type_name, Catch::Equals("Eigen::Matrix<double, -1, -1, 0, -1, -1>"));
    }
}

