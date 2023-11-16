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
    for (auto &p1: container) {
        p1.setOldF(p1.getFVector());
        VectorDouble3 f_i{};
        for (auto &p2: container) {
            if(!(p2 == p1)){
                f_i += this->forceCalculation.CalculateForces(p1,p2);
            }
        }
        p1.setF(f_i);
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
