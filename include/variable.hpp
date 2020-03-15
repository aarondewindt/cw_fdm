//
// Created by adewindt on 3/14/20.
//

#ifndef CW_SIM_VARIABLE_HPP
#define CW_SIM_VARIABLE_HPP

#include <string>
#include <any>
#include <utility>

#include "exception.hpp"
#include "fmt/format.h"

using namespace fmt::literals;


namespace cw::sim {
    template<class T>
    class MutableToken;

    template<class T>
    class ImmutableToken;

    class Variable {
        std::string name;
        bool mutable_token_created = false;

    public:
        template<class T>
        Variable(std::string name, T& initial_value) : name(std::move(name)), type_info(typeid(T)) {
            value = initial_value;
        };

        Variable() = delete;
        ~Variable() = default;
        Variable(const Variable&) = delete;
        Variable(Variable&&) noexcept = default;
        Variable& operator=(const Variable&) = delete;
        Variable& operator=(Variable&& other) noexcept = delete;

        const std::type_info& type_info;
        std::any value;

        std::string& get_name() {
            return name;
        }

        template<class T>
        MutableToken<T> create_mutable_token() {
            if (mutable_token_created) {
                throw MultipleMutableTokensCreatedError(
                        std::string("Only one mutable token may exist at a time."));
            }

            if ((type_info != typeid(T))) {
                throw TypeError(
                        "It's not possible to create a mutable token of type '{{type_1}}'. "
                        "Variable '{}' is of type '{{type_2}}'."_format(name), typeid(T), type_info);
            }

            mutable_token_created = true;
            return MutableToken<T>(*this);
        };

        template<class T>
        void return_mutable_token(MutableToken<T>& token) {
            token.is_mutable = false;
            mutable_token_created = false;
        }

        template<class T>
        ImmutableToken<T> create_immutable_token() {
            if ((type_info != typeid(T))) {
                throw TypeError(
                        "It's not possible to create a immutable token of type '{{type_1}}'. "
                        "Variable '{}' is of type '{{type_2}}'."_format(name), typeid(T), type_info);
            }

            return ImmutableToken<T>(*this);
        }

        const std::type_info& type() {
            return value.type();
        }
    };
}

#endif //CW_SIM_VARIABLE_HPP
