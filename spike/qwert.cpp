//
// Created by adewindt on 4/14/20.
//

#include <boost/numeric/odeint.hpp>
#include <iostream>

using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef std::vector< double > state_type;

const double gam = 0.15;

/* The rhs of x' = f(x) */
void harmonic_oscillator( const state_type &x , state_type &dxdt , const double /* t */ )
{
    dxdt[0] = x[1];
    dxdt[1] = -x[0] - gam*x[1];
}

int main() {
    state_type x(2);
    x[0] = 1.0; // start at x=1.0, p=0.0
    x[1] = 0.0;

    size_t steps = integrate( harmonic_oscillator ,
                              x , 0.0 , 10.0 , 0.1 );

    std::cout << steps << std::endl;
    return 0;
}
