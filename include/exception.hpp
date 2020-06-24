//
// Created by adewindt on 3/8/20.
//

#ifndef CW_SIM_EXCEPTION_HPP
#define CW_SIM_EXCEPTION_HPP

#include <exception>
#include <string>
#include <typeinfo>

#include "test_cw.hpp"
#include "fmt/core.h"


namespace cw::sim {
    /// \brief Generic exception type used as base by all errors thrown by the simulation.
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

    /// \brief Thrown if an unexpected type was encountered.
    class TypeError : public SimError {
    public:
        TypeError(const std::type_info& expected_type, const std::type_info& actual_type);
        TypeError(const std::string& format, const std::type_info& type_1, const std::type_info& type_2);
    };

    /// \brief Thrown if there is an attempt to create a second mutable token
    ///        linked to the same variable.
    class MultipleMutableTokensCreatedError : public SimError {
    public:
        explicit MultipleMutableTokensCreatedError(const std::string& message);
    };

    template<class T>
    class MutableToken;

    /// \brief Thrown if the is an attempt to mutate a variable through a
    ///        deactivated mutable token.
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



    /// \brief Thrown if the an attempt was made to create an immutable token to a non-existing
    ///        variable. This could happen if a module reading the variable is called before
    ///        the module writing to it.
    class CannotCreateImmutableTokenForNonExistingVariableError : public SimError {
        std::string variable_name;
    public:
        explicit CannotCreateImmutableTokenForNonExistingVariableError(const std::string& variable_name);
    };

    /// \brief Thrown if the is an attempt to mutate a variable through a
    ///        deactivated mutable token.
    template<class T, class Var>
    class ReturningMutableTokenToWrongVariableError : public SimError {
        MutableToken<T>& mutable_token;
    public:
        explicit ReturningMutableTokenToWrongVariableError(MutableToken<T>& mutable_token, Var& variable) :
                mutable_token(mutable_token),
                SimError(fmt::format("Returning mutable token for variable `{}` to variable `{}`.",
                                     mutable_token.get_variable().get_name(),
                                     variable.get_name()),
                         typeid(ReturningMutableTokenToWrongVariableError)) { };
    };

    /// \brief Thrown if the is an attempt to mutate a variable through a
    ///        deactivated mutable token.
    template<class T, class Var>
    class CheckingTokenActivityWithWrongVariable : public SimError {
        MutableToken<T>& mutable_token;
    public:
        explicit CheckingTokenActivityWithWrongVariable(MutableToken<T>& mutable_token, Var& variable) :
                mutable_token(mutable_token),
                SimError(fmt::format("Check mutable token for variable `{}` activity with variable `{}`.",
                                     mutable_token.get_variable().get_name(),
                                     variable.get_name()),
                         typeid(CheckingTokenActivityWithWrongVariable)) { };
    };

    /// \brief Thrown if the is an attempt to mutate a variable through a
    ///        deactivated mutable token.
    template<class T, class Var>
    class SettingVariableUsingWrongTokenError : public SimError {
        MutableToken<T>& mutable_token;
    public:
        explicit SettingVariableUsingWrongTokenError(MutableToken<T>& mutable_token, Var& variable) :
                mutable_token(mutable_token),
                SimError(fmt::format("Setting variable `{}` using token for variable `{}`.",
                                     variable.get_name(),
                                     mutable_token.get_variable().get_name()),
                         typeid(SettingVariableUsingWrongTokenError)) { };
    };
}

#endif //CW_SIM_EXCEPTION_HPP
