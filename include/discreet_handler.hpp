//
// Created by adewindt on 3/15/20.
//

#ifndef CW_SIM_DISCREET_HANDLER_HPP
#define CW_SIM_DISCREET_HANDLER_HPP

#include <functional>

#include "test_cw.hpp"
#include "handler.h"


namespace cw::sim {
    class DiscreetHandler : Handler {
        f64 dt;
        std::function<void(f64)> func;

    public:
        DiscreetHandler(std::function<void(f64)> func, f64 dt);
    };
}

#endif //CW_SIM_DISCREET_HANDLER_HPP
