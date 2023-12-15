#include "GravityForce.h"
#include "../../utils/VectorDouble3.h"

GravityForce::GravityForce(double gravity_factor_val) {
    gravity_factor = gravity_factor_val;
}

VectorDouble3 GravityForce::CalculateForces(const Particle &p) {
    //gravitational force G (along the y-axis) 
    double gravity = - p.getM()*gravity_factor;
    VectorDouble3 result (std::array<double,3> {0.0, gravity , 0.0});
    return result;
}

