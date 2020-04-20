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
        std::string name;  ///< \brief Variable name
        bool mutable_token_created = false;  ///< \brief True an active mutable token to this variable exists.

    public:
        /// \brief Initializes a new variable.
        ///
        /// \tparam T Variable value type.
        /// \param name Variable name
        /// \param initial_value Initial value.
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

        const std::type_info& type_info; ///< Type information of the variable value type.
        std::any value;  ///< Variable value.

        /// \brief Returns the variable name.
        /// \return Variable name
        std::string& get_name() {
            return name;
        }

        /// \brief Creates a mutable token linked to the variable.
        ///
        /// \warning In most cases tokens should be created by the VariableDatabase and
        ///          not this function.
        ///
        /// \tparam T Expected variable value type.
        /// \exception cw::sim::TypeError Type T does not match the variable value type.
        /// \exception cw::sim::MultipleMutableTokensCreatedError If an active mutable token
        ///            already exists for this variable.
        /// \return Mutable token linked to the variable.
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

        /// \brief Deactivates a mutable token linked to the variable.
        /// After deactivation the token cannot mutate the variable's value, but
        /// is still able to read it.
        ///
        /// \tparam T Derived, type of the variable value.
        /// \param token Mutable token to be returned.
        template<class T>
        void return_mutable_token(MutableToken<T>& token) {
            if (token.variable != this) {
                // TODO: Add some error msg here.
            }
            token.is_mutable = false;
            mutable_token_created = false;
        }

        /// \brief Create immutable token linked to the variable.
        ///
        /// \warning In most cases tokens should be created by the VariableDatabase and
        ///          not this function.
        ///
        /// \tparam T Expected variable value type.
        /// \exception cw::sim::TypeError Type T does not match the variable value type.
        /// \return Immutable token linked to the variable.
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
