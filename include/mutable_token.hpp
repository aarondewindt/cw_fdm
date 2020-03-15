//
// Created by adewindt on 3/14/20.
//

#ifndef CW_SIM_MUTABLE_TOKEN_HPP
#define CW_SIM_MUTABLE_TOKEN_HPP

#include "variable.hpp"
#include "exception.hpp"


namespace cw::sim {
    template<class T>
    class MutableToken {
        bool is_mutable = true;

        Variable& variable;
        explicit MutableToken(Variable& variable) : variable(variable) { };

        friend Variable;
    public:
        MutableToken() = delete;
        ~MutableToken() = default;
        MutableToken(MutableToken&) = delete;
        MutableToken(MutableToken&&) noexcept = default;
        MutableToken& operator=(const MutableToken&) = delete;
        MutableToken& operator=(MutableToken&& other) noexcept = default;

        Variable& get_variable() {
            return variable;
        }

        void deactivate() {
            variable.return_mutable_token(*this);
        };

        T get() {
            return std::any_cast<T>(variable.value);
        }

        void set(T& value) {
            if (is_mutable) {
                variable.value = value;
            } else {
                throw MutatingVariableUsingDeactivatedMutableTokenError(*this);
            }
        }

        void set(T&& value) {
            set(value);
        }

        const std::type_info& type() {
            return typeid(T);
        }
    };
}

#endif //CW_SIM_MUTABLE_TOKEN_HPP
