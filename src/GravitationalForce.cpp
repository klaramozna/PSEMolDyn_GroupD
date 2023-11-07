#include "GravitationalForce.h"
#include "VectorDouble.h"

#include <complex>

VectorDouble *GravitationalForce::CalculateForces(Particle &p1, Particle &p2) {
        this->result = ((p1.getM() * p2.getM()) / pow((p1.getXVector() - p2.getXVector()).getL2Norm(), 3)) * (p2.getXVector() - p1.getXVector());
        return &result;
};
