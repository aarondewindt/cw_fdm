//
// Created by adewindt on 3/14/20.
//

#ifndef CW_SIM_MUTABLE_TOKEN_HPP
#define CW_SIM_MUTABLE_TOKEN_HPP

#include "variable.hpp"
#include "exception.hpp"


namespace cw::sim {

    /// \brief Token with a read and write access to its variable.
    /// \tparam T Variable value type.
    template<class T>
    class MutableToken {
        /// True if the token is mutable, aka active. This is set to false when the
        /// is deactivated/returned to the variable..
        bool is_mutable = true;

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
        explicit MutableToken(Variable& variable) : variable(variable) { };

        friend Variable;
    public:
        MutableToken() = delete;
        ~MutableToken() = default;
        MutableToken(MutableToken&) = delete;
        MutableToken(MutableToken&&) noexcept = default;
        MutableToken& operator=(const MutableToken&) = delete;
        MutableToken& operator=(MutableToken&& other) noexcept = default;

        /// \brief Get a reference to the variable this token is linked to.
        /// \return Reference to the variable this token is linked to.
        Variable& get_variable() {
            return variable;
        }

        /// \brief Deactivate the token, aka return the token to the variable.
        void deactivate() {
            variable.return_mutable_token(*this);
        };

        /// Get the variable value.
        /// \return Variable value.
        T get() {
            return std::any_cast<T>(variable.value);
        }

        /// \brief Set the variable value.
        ///
        /// \exception cw::sim::MutatingVariableUsingDeactivatedMutableTokenError the
        ///            token has already been deactivated.
        /// \param value new variable value.
        void set(T& value) {
            if (is_mutable) {
                variable.value = value;
            } else {
                throw MutatingVariableUsingDeactivatedMutableTokenError(*this);
            }
        }

        /// \brief Set the variable value.
        ///
        /// \exception cw::sim::MutatingVariableUsingDeactivatedMutableTokenError the
        ///            token has already been deactivated.
        /// \param value new variable value.
        void set(T&& value) {
            set(value);
        }

        /// \brief Variable type information.
        /// \return
        const std::type_info& type() {
            return typeid(T);
        }
    };
}

#endif //CW_SIM_MUTABLE_TOKEN_HPP
