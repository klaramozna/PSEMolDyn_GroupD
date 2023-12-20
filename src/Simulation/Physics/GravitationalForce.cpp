#include "GravitationalForce.h"
#include "../../utils/VectorDouble3.h"


VectorDouble3 GravitationalForce::CalculateForces(const Particle &p1, const Particle &p2) {
    VectorDouble3 result{};

    // Check if the particles are not the same
    if (&p1 != &p2) {
        double distance = (p2.getXVector() - p1.getXVector()).getL2Norm();
        double distance_pow3 = distance * distance * distance;
        double forceMagnitude = (p1.getM() * p2.getM()) / distance_pow3;

        // Calculate force components
        result = scaleSIMD(forceMagnitude, (p2.getXVector() - p1.getXVector()));
    }

    return result;
}

