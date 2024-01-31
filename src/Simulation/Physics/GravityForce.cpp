#include "GravityForce.h"
#include "../../utils/VectorDouble3.h"

GravityForce::GravityForce(std::array<double,3>  gravity_factor_val) {
    gravity_factor = gravity_factor_val;
}

VectorDouble3 GravityForce::CalculateForce(const Particle &p) {
    VectorDouble3 result (gravity_factor);
    result = p.getM() * result;
    return result;
}

