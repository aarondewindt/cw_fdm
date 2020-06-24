//
// Created by adewindt on 4/21/20.
//

#include "catch2/catch.hpp"
#include "test_cw.hpp"
#include "variable.hpp"
#include "mutable_token.hpp"
#include "immutable_token.hpp"


using namespace Catch::literals;


namespace cw::sim::unittests {
    SCENARIO( "Variables can be created and accessed", "[token][variable]" ) {
        GIVEN("A new f64 variable created by moving the initial value.") {
            auto variable = Variable("foo", 8.64);

            WHEN("Get the name.") {
                auto name = variable.get_name();
                THEN("We get the correct variable name") {
                    CHECK_THAT(name, Catch::Equals("foo"));
                }
            }

            WHEN("Get variable type information") {
                const std::type_info& type = variable.type();
                THEN("It returned the type info of an f64.") {
                    CHECK(type == typeid(f64));
                }
            }

            WHEN( "Get the value with the correct type." ) {
                auto value = variable.get<f64>();
                THEN("We get the correct value") {
                    CHECK(value == 8.64_a);
                }
            }

            WHEN("Try to get value with the incorrect type.") {
                THEN("Throws a TypeError exception.") {
                    CHECK_THROWS_WITH(variable.get<i32>(),
                                      "cw::sim::TypeError: Variable 'foo' is of type "
                                      "'double', but tried to get value of type 'int'.");
                }
            }

            WHEN("Create a mutable token from the variable with the correct type.") {
                MutableToken<f64> mutable_token = variable.create_mutable_token<f64>();

                THEN("Get active mutable token") {
                    CHECK(mutable_token.is_active());
                    CHECK(variable.is_mutable_token_active(mutable_token));
                }

                WHEN("Get value type from token.") {
                    const std::type_info& type = mutable_token.type();
                    THEN("It returned the type info of an f64.") {
                        CHECK(type == typeid(f64));
                    }
                }

                WHEN ("Get reference to variable from the token.") {
                    Variable& var_reference = mutable_token.get_variable();
                    THEN("Variable reference references the existing variable") {
                        CHECK(&var_reference == &variable);
                    }
                }

                WHEN("Set value through the variable by passing the token and moving the value.") {
                    variable.set(mutable_token, 3.56);

                    THEN("New value is read from the variable.") {
                        CHECK(variable.get<f64>() == 3.56_a);
                    }
                }

                WHEN("Set value through the variable by passing the token and reference to the value.") {
                    f64 new_value = 7.36;
                    variable.set(mutable_token, new_value);

                    THEN("New value is read from the variable.") {
                        CHECK(variable.get<f64>() == 7.36_a);
                    }
                }

                WHEN("Set value through the token by moving the value.") {
                    mutable_token.set(12.4);
                    THEN("New value is read from the variable.") {
                        CHECK(variable.get<f64>() == 12.4_a);
                    }
                }

                WHEN("Set value through the token by passing a reference to the value.") {
                    f64 new_value = 97.6;
                    mutable_token.set(new_value);

                    THEN("New value is read from the variable.") {
                        CHECK(variable.get<f64>() == 97.6_a);
                    }
                }

                WHEN("Get value through the token.") {
                    f64 value = mutable_token.get();
                    CHECK(value == 8.64);
                }

                WHEN("Try to create a second mutable token.") {
                    THEN("MultipleMutableTokensCreatedError is thrown.") {
                        CHECK_THROWS_WITH(variable.create_mutable_token<f64>(),
                                "cw::sim::MultipleMutableTokensCreatedError: Only one mutable token may exist at a time.");
                    }
                }

                WHEN("Deactivate the mutable token.") {
                    mutable_token.deactivate();
                    THEN("Token known its inactive") {
                        CHECK(!mutable_token.is_active());
                    }

                    WHEN("Get the value from the deactivated token.") {
                        f64 value = mutable_token.get();
                        THEN("Get the value as normal."){
                            CHECK(value == 8.64);
                        }
                    }

                    WHEN("Set the value from the deactivated token.") {
                        CHECK_THROWS_WITH(mutable_token.set(12.4),
                                          "cw::sim::MutatingVariableUsingDeactivatedMutableTokenError<double>: "
                                          "Mutating variable 'foo' using a 'cw::sim::MutableToken<double>' that has "
                                          "been deactivated.");
                    }

                    WHEN("Create new mutable token.") {
                        MutableToken<f64> mutable_token_2 = variable.create_mutable_token<f64>();
                        THEN("We get a new active mutable token.") {
                            CHECK(mutable_token_2.is_active());
                        }
                        WHEN("Set the value using the new token.") {
                            mutable_token_2.set(846.3);
                            THEN("The new value is read from the variable.") {
                                CHECK(variable.get<f64>() == 846.3_a);
                            }
                        }
                    }
                }

                WHEN("Create a second variable.") {
                    auto variable_2 = Variable("bar", 74.3);
                    WHEN("Return the first token to the second variable.") {
                        THEN("Error is thrown.") {
                            CHECK_THROWS_WITH(variable_2.return_mutable_token(mutable_token),
                                    "cw::sim::ReturningMutableTokenToWrongVariableError<double, "
                                    "cw::sim::Variable>: Returning mutable token for variable `foo` to "
                                    "variable `bar`.");
                        }
                    }

                    WHEN("Check the first token activity using the second variable.") {
                        THEN("Error is thrown.") {
                            CHECK_THROWS_WITH(variable_2.is_mutable_token_active(mutable_token),
                                    "cw::sim::CheckingTokenActivityWithWrongVariable<double, "
                                    "cw::sim::Variable>: Check mutable token for variable `foo` "
                                    "activity with variable `bar`.");
                        }
                    }

                    WHEN("Check the first token activity using the second variable.") {
                        THEN("Error is thrown.") {
                            CHECK_THROWS_WITH(variable_2.set(mutable_token, 12.3),
                                    "cw::sim::SettingVariableUsingWrongTokenError<double, "
                                    "cw::sim::Variable>: Setting variable `bar` using token for variable `foo`.");
                        }
                    }
                }

            }

            WHEN("Create mutable token from the variable with the incorrect type") {
                CHECK_THROWS_WITH(variable.create_mutable_token<i32>(),
                        "cw::sim::TypeError: It's not possible to create a mutable "
                        "token of type 'int'. Variable 'foo' is of type 'double'.");
            }

            WHEN("Create a immutable token from the variable using the correct type.")  {
                auto immutable_token = variable.create_immutable_token<f64>();
                
            }
        }
    }
}


