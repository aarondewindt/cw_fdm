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


namespace cw::sim {
    class VariableDatabase {
        std::map<std::string, Variable> variables_map;
    public:
        VariableDatabase();

        template<class T>
        MutableToken<T> create_mutable_token(const std::string& name, T& initial_value) {
            auto [iter, new_created] = variables_map.emplace(std::piecewise_construct,
                                                             std::forward_as_tuple(name),
                                                             std::forward_as_tuple(name, initial_value));

            Variable& variable = iter->second;
            return variable.create_mutable_token<T>();
        };

        template<class T>
        MutableToken<T> create_mutable_token(const std::string& name, T&& initial_value) {
            return create_mutable_token(name, initial_value);
        }

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
