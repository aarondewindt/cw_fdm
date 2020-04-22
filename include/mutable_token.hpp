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
        /// Variable the token is linked to.
        Variable& variable;

        const u32 token_id;

        /// \brief Constructor.
        ///
        /// For safety we want all tokens to be created by their variable. This way
        /// the variable is able to keep track of all its tokens and which ones have
        /// what kind of access.
        /// Tho achieve this the constructor to this class is made private and the
        /// Variable class a friend.
        ///
        /// \param variable
        explicit MutableToken(Variable& variable, u32 token_id) :
            variable(variable),
            token_id(token_id) { };

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

        bool is_active() {
            return variable.is_mutable_token_active(*this);
        }

        /// Get the variable value.
        /// \return Variable value.
        T get() {
            return variable.get<T>();
        }

        /// \brief Set the variable value.
        ///
        /// \exception cw::sim::MutatingVariableUsingDeactivatedMutableTokenError the
        ///            token has already been deactivated.
        /// \param value new variable value.
        void set(T& value) {
            variable.set<T>(*this, value);
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
