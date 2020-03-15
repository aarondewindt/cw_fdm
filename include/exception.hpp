//
// Created by adewindt on 3/8/20.
//

#ifndef CW_SIM_EXCEPTION_HPP
#define CW_SIM_EXCEPTION_HPP

#include <exception>
#include <string>
#include <typeinfo>

#include "cw.hpp"
#include "fmt/core.h"


namespace cw::sim {
    class SimError : public std::exception {
        const std::type_info& exception_type_id;
        std::string msg;

    protected:
        void set_msg(const std::string& message);

    public:
        SimError();
        explicit SimError(const std::type_info& exception_type_id);
        SimError(const std::string& message, const std::type_info& exception_type_id);

        [[nodiscard]] const char* what() const noexcept override;
    };

    class TypeError : public SimError {
    public:
        TypeError(const std::type_info& expected_type, const std::type_info& actual_type);
        TypeError(const std::string& format, const std::type_info& type_1, const std::type_info& type_2);
    };

    class MultipleMutableTokensCreatedError : public SimError {
    public:
        explicit MultipleMutableTokensCreatedError(const std::string& message);
    };

    template<class T>
    class MutableToken;

    template<class T>
    class MutatingVariableUsingDeactivatedMutableTokenError : public SimError {
        MutableToken<T>& mutable_token;
    public:
        explicit MutatingVariableUsingDeactivatedMutableTokenError(MutableToken<T>& mutable_token) :
            mutable_token(mutable_token),
            SimError(fmt::format("Mutating variable '{}' using a '{}' that has been deactivated.",
                                 mutable_token.get_variable().get_name(),
                                 get_type_name(typeid(MutableToken<T>))),
                     typeid(MutatingVariableUsingDeactivatedMutableTokenError)) { };
    };

    class Variable;

    class CannotCreateImmutableTokenForNonExistingVariableError : public SimError {
        std::string variable_name;
    public:
        explicit CannotCreateImmutableTokenForNonExistingVariableError(const std::string& variable_name);
    };
}

#endif //CW_SIM_EXCEPTION_HPP
