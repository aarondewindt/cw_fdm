// Add include paths
#pragma cling add_include_path("../include")
#pragma cling add_include_path("../lib/eigen")
#pragma cling add_include_path("../lib/span/include")
#pragma cling add_include_path("../lib/fmt/include")
// #pragma cling add_include_path("../lib/boost/libs/numeric/odeint/include")
// #pragma cling add_include_path("../lib/boost/libs/numeric/ublas/include")
// #pragma cling add_include_path("../lib/boost/libs/config/include")
// #pragma cling add_include_path("../lib/boost/libs/type_traits/include")
// #pragma cling add_include_path("../lib/boost/libs/serialization/include")
// #pragma cling add_include_path("../lib/boost/libs/core/include")
// #pragma cling add_include_path("../lib/boost/libs/preprocessor/include")
// #pragma cling add_include_path("../lib/boost/libs/static_assert/include")
// #pragma cling add_include_path("../lib/boost/libs/mpl/include")
// #pragma cling add_include_path("../lib/boost/libs/utility/include")
// #pragma cling add_include_path("../lib/boost/libs/typeof/include")
// #pragma cling add_include_path("../lib/boost/libs/array/include")
// #pragma cling add_include_path("../lib/boost/libs/assert/include")
// #pragma cling add_include_path("../lib/boost/libs/throw_exception/include")
// #pragma cling add_include_path("../lib/boost/libs/units/include")
// #pragma cling add_include_path("../lib/boost/libs/integer/include")
// #pragma cling add_include_path("../lib/boost/libs/fusion/include")
// #pragma cling add_include_path("../lib/boost/libs/range/include")
// #pragma cling add_include_path("../lib/boost/libs/iterator/include")
// #pragma cling add_include_path("../lib/boost/libs/concept_check/include")
// #pragma cling add_include_path("../lib/boost/libs/detail/include")
// #pragma cling add_include_path("../lib/boost/libs/function_types/include")
// #pragma cling add_include_path("../lib/boost/libs/predef/include")
// #pragma cling add_include_path("../lib/boost/libs/math/include")
// #pragma cling add_include_path("../lib/boost/libs/lexical_cast/include")
// #pragma cling add_include_path("../lib/boost/libs/numeric/conversion/include")
// #pragma cling add_include_path("../lib/boost/libs/container/include")
// #pragma cling add_include_path("../lib/boost/libs/move/include")
// #pragma cling add_include_path("../lib/boost/libs/smart_ptr/include")
// #pragma cling add_include_path("../lib/boost/libs/multi_array/include")
// #pragma cling add_include_path("../lib/boost/libs/functional/include")
// #pragma cling add_include_path("../lib/boost/libs/function/include")
// #pragma cling add_include_path("../lib/boost/libs/type_index/include")
// #pragma cling add_include_path("../lib/boost/libs/container_hash/include")
// #pragma cling add_include_path("../lib/boost/libs/bind/include")

// Add shared libraries
#pragma cling add_library_path("../cmake-build-debug")
#pragma cling load("libcw_sim")

// Include from the standard library
#include <any>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>
#include <array>

// Include third party libraries.
#include "boost/numeric/odeint.hpp"

#define TCB_SPAN_NAMESPACE_NAME std
#include "tcb/span.hpp"

// Inlude project.
#include "cw.hpp"
#include "variables_database.hpp"


// Most of the code in the project is inside the cw::sim namespace.
// So lets use it so that we minimize the amount of cleaning 
// we'll have to do when copy pasting code form the notebooks.
using namespace cw;
using namespace cw::sim;

// Because I'm lazy
using std::cout;
using std::endl;
namespace odeint = boost::numeric::odeint;
