//
// Created by adewindt on 3/8/20.
//

#include <utility>
#include <iostream>

#include "cw.hpp"
#include "exception.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

using namespace fmt::literals;

namespace cw::sim {
    SimError::SimError() :
            exception_type_id(typeid(SimError)),
            msg(fmt::format("{}: {}", get_type_name(exception_type_id), msg)) {
    }

    SimError::SimError(const std::type_info& exception_type_id) :
            msg(fmt::format("{}: {}", get_type_name(exception_type_id), "Simulation error")),
            exception_type_id(exception_type_id) { }

    SimError::SimError(const std::string& message, const std::type_info& exception_type_id) :
            msg(fmt::format("{}: {}", get_type_name(exception_type_id), message)),
            exception_type_id(exception_type_id) { }

    [[nodiscard]] const char* SimError::what() const noexcept {
        return msg.c_str();
    }

    void SimError::set_msg(const std::string& message) {
        this->msg = fmt::format("{}: {}", get_type_name(exception_type_id), message);
    }

    MultipleMutableTokensCreatedError::MultipleMutableTokensCreatedError(const std::string& message) :
            SimError(message, typeid(MultipleMutableTokensCreatedError)) {
    }

    TypeError::TypeError(const std::type_info& expected_type, const std::type_info& actual_type) :
            SimError(typeid(TypeError))
    {
        auto expected_type_name = get_type_name(expected_type);
        auto actual_type_name = get_type_name(actual_type);
        set_msg("Expected '" + expected_type_name + "', got '" + actual_type_name + "' instead.");
    }

    TypeError::TypeError(const std::string& format, const std::type_info &type_1, const std::type_info &type_2) :
            SimError(typeid(TypeError))
    {
        set_msg(fmt::format(format, "type_1"_a=get_type_name(type_1), "type_2"_a=get_type_name(type_2)));
    }

    CannotCreateImmutableTokenForNonExistingVariableError::CannotCreateImmutableTokenForNonExistingVariableError(
            const std::string& variable_name) :
                SimError("Cannot create an immutable token for a non-existing variable {}. "_format(variable_name) +
                         "Maybe try creating a mutable token first.",
                         typeid(CannotCreateImmutableTokenForNonExistingVariableError)),
                variable_name(variable_name) { }
}