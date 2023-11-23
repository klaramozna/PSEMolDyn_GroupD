//
// Created by rodff on 22.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERSTUB_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERSTUB_H

#include "Particle.h"
#include <functional>

class LinkedCellContainerStub {
public:
    virtual void addParticle(Particle &particle);
    virtual void addParticles(std::vector<Particle> &particles);
    virtual size_t getSize();
    virtual void applyToAll(const std::function<void(Particle&)>& function);
    virtual void applyToPair(const std::function<void(Particle&, Particle&)>& function);
    virtual std::vector<Particle>& getParticleVector();
    virtual void applyToBoundary(const std::function<void(Particle(&))>& function);
    virtual void applyToHalo(const std::function<void(Particle&)>& function);
    virtual void deleteHaloParticles();
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERSTUB_H
