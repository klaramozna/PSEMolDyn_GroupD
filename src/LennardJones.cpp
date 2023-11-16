#include "LennardJones.h"
#include "VectorDouble3.h"

#include <complex>

VectorDouble3 *LennardJones::CalculateForces(Particle &p1, Particle &p2) {
        //Cache Repeated Computations
        VectorDouble3 distance = p1.getXVector() - p2.getXVector();
        double distanceL2Norm = distance.getL2Norm();
        double sigma_term = sigma / distanceL2Norm;
        double sigma_term_pow2 = sigma_term * sigma_term;
        double sigma_term_pow_6 = sigma_term_pow2 * sigma_term_pow2 * sigma_term_pow2;
        double sigma_term_pow_12 = sigma_term_pow_6 * sigma_term_pow_6;
        result = (-24 * eps / pow(distanceL2Norm,2)) * (sigma_term_pow_6 - 2 * sigma_term_pow_12) * distance;
        return &result;
};
