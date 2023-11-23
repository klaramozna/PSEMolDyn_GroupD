//
// Created by rodff on 23.11.23.
//

#include "ReflectingBoundaryForce.h"

void ReflectingBoundaryForce::processBoundary(LinkedCellContainerStub &container,
                                                      ForceCalculation &forceCalculation) {
    double sigma = 0.0;
    container.applyToBoundary([this, &forceCalculation, sigma](Particle &particle){
        std::vector<std::array<double,3>> ghostParticleCoords = this->findOppositeParticles(particle);
        for (auto vector : ghostParticleCoords) {
            Particle ghostParticle{vector, {0.0, 0.0, 0.0} , particle.getM()};
            if ((VectorDouble3(vector) - particle.getXVector()).getL2Norm() < (sixthRootOf2 * sigma))
                particle.setOldF(particle.getFVector() + forceCalculation.CalculateForces(particle, ghostParticle));
        }
    });
}