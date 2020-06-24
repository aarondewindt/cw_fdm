//
// Created by adewindt on 4/14/20.
//

#ifndef CW_SIM_BOOST_ODEINT_EXPERIMENT_H
#define CW_SIM_BOOST_ODEINT_EXPERIMENT_H

#include <any>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <array>

#include "boost/numeric/odeint.hpp"

#define TCB_SPAN_NAMESPACE_NAME std
#include "tcb/span.hpp"
// #include "Eigen/Dense"

#include "cw.hpp"
#include "variables_database.hpp"
#include "mutable_token.hpp"
#include "immutable_token.hpp"
#include "variable.hpp"


using namespace cw;
using namespace cw::sim;

using std::cout;
using std::endl;

namespace odeint = boost::numeric::odeint;

#endif //CW_SIM_BOOST_ODEINT_EXPERIMENT_H
