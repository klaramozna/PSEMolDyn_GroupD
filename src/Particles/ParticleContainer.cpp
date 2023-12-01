//
// Created by klara on 21.11.23.
//

#include "ParticleContainer.h"

void ParticleContainer::addParticles(const std::vector<Particle>& toAdd) {
    for(auto & p : toAdd){
        addParticle(p);
    }
}
