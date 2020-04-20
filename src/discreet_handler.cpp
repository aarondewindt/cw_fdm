//
// Created by adewindt on 3/15/20.
//

#include "discreet_handler.h"

#include <utility>


namespace cw::sim {
    DiscreetHandler::DiscreetHandler(std::function<void (f64)> func, f64 dt) : func(std::move(func)), dt(dt) { }
}
