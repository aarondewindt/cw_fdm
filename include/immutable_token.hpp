//
// Created by adewindt on 3/14/20.
//

#ifndef CW_SIM_IMMUTABLE_TOKEN_HPP
#define CW_SIM_IMMUTABLE_TOKEN_HPP

#include "variable.hpp"


namespace cw::sim {
    /// \brief Token with a read only access to its variable.
    /// \tparam T Variable value type.
    template<class T>
    class ImmutableToken {
        /// Variable the token is linked to.
        Variable& variable;

        /// \brief Constructor.
        ///
        /// For safety we want all tokens to be created by their variable. This way
        /// the variable is able to keep track of all its tokens and which ones have
        /// what kind of access.
        /// Tho achieve this the constructor to this class is made private and the
        /// Variable class a friend.
        ///
        /// \param variable
        explicit ImmutableToken(Variable& variable) : variable(variable) { };
        friend Variable;
    public:
        ImmutableToken() = delete;
        ~ImmutableToken() = default;
        ImmutableToken(const ImmutableToken&) = delete;
        ImmutableToken(ImmutableToken&&) noexcept = default;
        ImmutableToken& operator=(const ImmutableToken&) = delete;
        ImmutableToken& operator=(ImmutableToken&& other) noexcept = default;

        /// Get the variable value.
        /// \return Variable value.
        T get() {
            return std::any_cast<T>(variable.value);
        }

        /// \brief Variable type information.
        /// \return
        const std::type_info& type() {
            return typeid(T);
        }
    };
}

#endif //CW_SIM_IMMUTABLE_TOKEN_HPP
