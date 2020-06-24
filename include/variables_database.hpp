//
// Created by adewindt on 3/7/20.
//

#ifndef CW_SIM_VARIABLES_DATABASE_HPP
#define CW_SIM_VARIABLES_DATABASE_HPP

#include <map>
#include <string>
#include <any>
#include <tuple>
#include <utility>

#include "exception.hpp"
#include "variable.hpp"
#include "fmt/core.h"


namespace cw::sim {
    /// \brief Variable database.
    ///
    /// Creates, contains and destroys variables and tokens.
    ///
    /// \tparam T
    /// \param name
    /// \param initial_value
    /// \param force_value
    /// \return
    class VariableDatabase {
        std::map<std::string, Variable> variables_map;
    public:
        VariableDatabase();

        /// \brief Create new mutable token linked to the variable with the given name.
        ///
        /// If a variable with the given name does not exists, it will be created.
        /// If the variable already exist, the variable will keep its current value, unless
        /// force_value is set to true.
        ///
        /// \tparam T Expected variable type.
        /// \param name Variable name
        /// \param initial_value Initial variable value if a new variable needs to be created.
        /// \param force_value If true the variable will be set to the initial_value whether
        ///                    its new or not.
        /// \exception cw::sim::TypeError Type T does not match the variable value type.
        /// \exception cw::sim::MultipleMutableTokensCreatedError If an active mutable token
        ///            already exists for this variable.
        /// \return Mutable token to the variable.
        template<class T>
        MutableToken<T> create_mutable_token(const std::string& name, T& initial_value, bool force_value=false) {
            auto [iter, new_created] = variables_map.emplace(std::piecewise_construct,
                                                             std::forward_as_tuple(name),
                                                             std::forward_as_tuple(name, initial_value));
            Variable& variable = iter->second;

            auto token = variable.create_mutable_token<T>();

            if (!new_created) {
                if (force_value) {
                    if (typeid(T) == variable.type()) {
                         variable.set(token, initial_value);
                    } else {
                        throw TypeError(fmt::format("Cannot create new mutable token of type '{{type_1}} for "
                                        "existing variable '{name}' of type {{type_2}}.", variable.get_name()),
                                                typeid(T), variable.type());
                    }
                }
            }

            return token;
        };

        /// \brief Create new mutable token linked to the variable with the given name.
        ///
        /// If a variable with the given name does not exists, it will be created.
        /// If the variable already exist, the variable will keep its current value, unless
        /// force_value is set to true.
        ///
        /// \tparam T Expected variable type.
        /// \param name Variable name
        /// \param initial_value Initial variable value if a new variable needs to be created.
        /// \param force_value If true the variable will be set to the initial_value whether
        ///                    its new or not.
        /// \exception cw::sim::TypeError Type T does not match the variable value type.
        /// \exception cw::sim::MultipleMutableTokensCreatedError If an active mutable token
        ///            already exists for this variable.
        /// \return Mutable token to the variable.
        template<class T>
        MutableToken<T> create_mutable_token(const std::string& name, T&& initial_value, bool force_value=false) {
            return create_mutable_token(name, initial_value, force_value);
        }

        /// \brief Create new immutable token linked to the variable with the given name.
        ///
        /// \tparam T Expected variable type.
        /// \param name Variable name
        /// \exception cw::sim::TypeError Type T does not match the variable value type.
        /// \exception cw::sim::CannotCreateImmutableTokenForNonExistingVariableError If
        ///            the variable has not been created yet.
        /// \return Immutable token to the variable.
        template<class T>
        ImmutableToken<T> create_immutable_token(const std::string& name) {
            auto result = variables_map.find(name);
            if (result != variables_map.end()) {
                Variable& variable = result->second;
                return variable.create_immutable_token<T>();
            } else {
                throw CannotCreateImmutableTokenForNonExistingVariableError(name);
            }
        };
    };
}

#endif //CW_SIM_VARIABLES_DATABASE_HPP
