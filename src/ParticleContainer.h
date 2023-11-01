//
// Created by klara on 30.10.23.
//

#ifndef PSEMOLDYN_PARTICLECONTAINER_H
#define PSEMOLDYN_PARTICLECONTAINER_H

#include <vector>
#include "Particle.h"


class ParticleContainer {
private:
    std::vector<Particle> particles;
public:
    typedef std::vector<Particle>::iterator iterator_type;
    explicit ParticleContainer(std::vector<Particle> particles);
    ParticleContainer() = default;
    iterator_type begin();
    iterator_type end();
    void addParticle(Particle particle);
    void addParticles(std::vector<Particle> toAdd);
};


#endif //PSEMOLDYN_PARTICLECONTAINER_H
