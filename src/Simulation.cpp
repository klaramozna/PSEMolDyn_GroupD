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

void Simulation::calculateF() {
    // updating the old force and setting the new force to zero
    for(auto & p : container){
        p.setOldF((p.getFVector()));
        p.setF(VectorDouble3());
    }

    // calculating the new force
    for(auto it = container.beginPair(); it != container.endPair(); ++it){
        Particle& p1 = (*it).first;
        Particle& p2 = (*it).second;
        p1.setF(p1.getFVector() + *(this->forceCalculation.CalculateForces(p1,p2)));
        p2.setF(p2.getFVector() + *(this->forceCalculation.CalculateForces(p2,p1)));
    }


}

void Simulation::calculateV() {
    for (auto &p: container) {
        VectorDouble3 v_i = p.getVVector() + (this->delta_t / (2. * p.getM()) * (p.getOldFVector() + p.getFVector()));
        p.setV(v_i);
    }
}

void Simulation::calculateX() {
    for (auto &p: container) {
        VectorDouble3 x_i = p.getXVector() + delta_t * p.getVVector()
                           + ((delta_t * delta_t) / (2. * p.getM())) * p.getOldFVector();
        p.setX(x_i);
    }
}

void Simulation::runIteration() {
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();
}
