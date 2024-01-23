#include "HardcodedPullForce.h"
#include "../../utils/VectorDouble3.h"

HardcodedPullForce::HardcodedPullForce(std::array<double,3>  pull_factors_val) {
    pull_factors = pull_factors_val;
}

VectorDouble3 HardcodedPullForce::CalculateForce(const Particle &p) {
    VectorDouble3 result (pull_factors);
    return result;
}

