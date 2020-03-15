//
// Created by adewindt on 3/14/20.
//

#ifndef CW_SIM_IMMUTABLE_TOKEN_HPP
#define CW_SIM_IMMUTABLE_TOKEN_HPP

#include "variable.hpp"


namespace cw::sim {
    template<class T>
    class ImmutableToken {
        Variable& variable;
        explicit ImmutableToken(Variable& variable) : variable(variable) { };
        friend Variable;
    public:
        ImmutableToken() = delete;
        ~ImmutableToken() = default;
        ImmutableToken(const ImmutableToken&) = delete;
        ImmutableToken(ImmutableToken&&) noexcept = default;
        ImmutableToken& operator=(const ImmutableToken&) = delete;
        ImmutableToken& operator=(ImmutableToken&& other) noexcept = default;

        T get() {
            return std::any_cast<T>(variable.value);
        }

        const std::type_info& type() {
            return typeid(T);
        }
    };
}

#endif //CW_SIM_IMMUTABLE_TOKEN_HPP
