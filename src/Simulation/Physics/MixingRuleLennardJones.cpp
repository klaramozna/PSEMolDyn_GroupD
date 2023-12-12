//
// Created by klara on 12.12.23.
//

#include "MixingRuleLennardJones.h"
#include <cmath>

VectorDouble3 MixingRuleLennardJones::CalculateForces(const Particle &p1, const Particle &p2) {
    VectorDouble3 result{};
    double sigma = (p1.getSigma() + p2.getSigma()) / 2;
    double eps = sqrt(p1.getEpsilon() * p1.getEpsilon());
    //Cache Repeated Computations
    VectorDouble3 distance = p1.getXVector() - p2.getXVector();
    double distanceL2Norm = distance.getL2Norm();
    double sigma_term = sigma / distanceL2Norm;
    double sigma_term_pow2 = sigma_term * sigma_term;
    double sigma_term_pow_6 = sigma_term_pow2 * sigma_term_pow2 * sigma_term_pow2;
    double sigma_term_pow_12 = sigma_term_pow_6 * sigma_term_pow_6;
    double distanceL2Norm_pow2 = distanceL2Norm * distanceL2Norm;
    result = (-24 * eps / distanceL2Norm_pow2) * (sigma_term_pow_6 - 2 * sigma_term_pow_12) * distance;
    return result;
}
