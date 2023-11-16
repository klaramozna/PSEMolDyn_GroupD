/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include "Simulation.h"
#include "VectorDouble3.h"
#include "ForceCalculation.h"

#include <utility>

Simulation::Simulation(double delta_t,
                       ParticleContainer container,
                       ForceCalculation &calculation) :
                        container(std::move(container)),
                        forceCalculation(calculation),
                        delta_t(delta_t) {}

Simulation::~Simulation() = default;

ParticleContainer& Simulation::getParticles() {
    return container;
}

void Simulation::calculateF(Particle& p1, Particle& p2) {
    p1.setF(p1.getFVector() + *(this->forceCalculation.CalculateForces(p1,p2)));
    p2.setF(p2.getFVector() + *(this->forceCalculation.CalculateForces(p2,p1)));
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
