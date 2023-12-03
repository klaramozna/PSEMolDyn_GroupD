//
// Created by rodff on 22.11.23.
//

#include "ReflectingBoundaryGhostParticle.h"

void ReflectingBoundaryGhostParticle::processBoundary(LinkedCellContainer &container) {
    double sigma = 0.0;
    container.applyToBoundary([this, &container, sigma](Particle &particle){
        std::vector<std::array<double,3>> ghostParticleCoords = this->findOppositeParticles(particle);
        for (auto vector : ghostParticleCoords) {
            Particle ghostParticle{vector, {0.0, 0.0, 0.0} , particle.getM()};
            if ((VectorDouble3(vector) - particle.getXVector()).getL2Norm() < (sixthRootOf2 * sigma))
                container.addParticle(ghostParticle);
        }
    });
}
