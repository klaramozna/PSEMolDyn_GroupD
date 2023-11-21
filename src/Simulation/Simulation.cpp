/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include "Simulation.h"
#include "../utils/VectorDouble3.h"
#include "./Physics/ForceCalculation.h"
#include "../utils/MaxwellBoltzmannDistribution.h"

#include <utility>

Simulation::Simulation(double delta_t,
                       DirectSumContainer container,
                       ForceCalculation &calculation,
                       double averageVelo) :
                        container(std::move(container)),
                        forceCalculation(calculation),
                        delta_t(delta_t),
                        averageVelo(averageVelo) {
        this->container.applyToAll([this](Particle& particle){
            VectorDouble3 randomVelo(maxwellBoltzmannDistributedVelocity(this->averageVelo, 3));
            particle.setV(randomVelo);
    });
}

Simulation::~Simulation() = default;

DirectSumContainer& Simulation::getParticles() {
    return container;
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
    container.applyToAll([this](Particle& p) { calculateX(p); });
    // calculate new f
    container.applyToAll([](Particle& p) { setOldForce(p); });
    container.applyToPairs([this](Particle& p1, Particle& p2) { calculateF(p1, p2); });
    // calculate new v
    container.applyToAll([this](Particle& p) { calculateV(p); });
}

void Simulation::setOldForce(Particle& p) {
    p.setOldF((p.getFVector()));
    p.setF(VectorDouble3());
}