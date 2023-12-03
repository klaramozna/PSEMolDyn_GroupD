/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include "Simulation.h"
#include "../utils/MaxwellBoltzmannDistribution.h"

#include <utility>

Simulation::Simulation(double delta_t,
                       std::unique_ptr<ParticleContainer> &&container_,
                       ForceCalculation &calculation,
                       double averageVelo,
                       std::unique_ptr<Boundary> &&boundary) :
                        container_{std::move(container_)},
                        forceCalculation{calculation},
                        boundary{std::move(boundary)},
                        delta_t{delta_t},
                        averageVelo{averageVelo} {
        this->container_->applyToAll([this](Particle& particle){
            VectorDouble3 randomVelo(maxwellBoltzmannDistributedVelocity(this->averageVelo, 3));
            particle.setV(randomVelo);
    });
}

Simulation::~Simulation() = default;

std::vector<Particle>& Simulation::getParticles() {
    return container_->getParticleVector();
}


void Simulation::calculateF(Particle& p1, Particle& p2) {
    VectorDouble3 result = this->forceCalculation.CalculateForces(p1,p2);
    p1.setF(p1.getFVector() + result);
    p2.setF(p2.getFVector() - result);
}

void Simulation::calculateV(Particle& p) const {
    VectorDouble3 v_i = p.getVVector() + (this->delta_t / (2. * p.getM()) * (p.getOldFVector() + p.getFVector()));
    p.setV(v_i);
}

void Simulation::calculateX(Particle& p) const {
    VectorDouble3 x_i = p.getXVector() + delta_t * p.getVVector()
            + ((delta_t * delta_t) / (2. * p.getM())) * p.getOldFVector();
    p.setX(x_i);
}

void Simulation::runIteration() {
    // calculate new x
    container_->applyToAll([this](Particle& p) { calculateX(p); });
    // calculate new f
    container_->applyToAll([](Particle& p) { setOldForce(p); });

    container_->applyBoundaryConditions(*boundary);

    container_->applyToPairs([this](Particle& p1, Particle& p2) { calculateF(p1, p2); });
    // calculate new v
    container_->applyToAll([this](Particle& p) { calculateV(p); });

}

void Simulation::setOldForce(Particle& p) {
    p.setOldF((p.getFVector()));
    p.setF(VectorDouble3());
}
