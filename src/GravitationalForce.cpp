#include "GravitationalForce.h"
#include "VectorDouble3.h"

#include <complex>

VectorDouble3 GravitationalForce::CalculateForces(const Particle &p1, const Particle &p2) {
    VectorDouble3 result{};

    // Check if the particles are not the same
    if (&p1 != &p2) {
        double distance = (p2.getXVector() - p1.getXVector()).getL2Norm();
        double forceMagnitude = (p1.getM() * p2.getM()) / pow(distance, 3);

        // Calculate force components
        result = forceMagnitude * (p2.getXVector() - p1.getXVector());
    }

    return result;
}

