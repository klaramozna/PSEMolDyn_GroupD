//
// Created by klara on 30.10.23.
//

#include "ParticleContainer.h"

#include <utility>

std::vector<Particle>::iterator ParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator ParticleContainer::end() {
    return particles.end();
}

ParticleContainer::ParticleContainer(std::vector<Particle> particles) {
    this->particles = std::move(particles);
}

void ParticleContainer::addParticle(Particle particle) {
    this->particles.push_back(particle);
}

void ParticleContainer::addParticles(std::vector<Particle> toAdd) {
    particles.insert(particles.end(), toAdd.begin(), toAdd.end());
}
