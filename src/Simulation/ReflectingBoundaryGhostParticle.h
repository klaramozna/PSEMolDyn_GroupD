//
// Created by rodff on 23.11.23.
//

#include "ReflectingBoundary.h"

class ReflectingBoundaryGhostParticle : public ReflectingBoundary {
public:
    virtual void processBoundary(LinkedCellContainerStub &container, ForceCalculation &forceCalculation) override;
protected:
    virtual std::vector<std::array<double,3>> findOppositeParticles(Particle &particle) override;
};