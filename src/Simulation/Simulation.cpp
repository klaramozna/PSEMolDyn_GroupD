/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include "Simulation.h"

#include "Particles/LinkedCellContainer.h"
#include "Particles/BoundaryEnforcer.h"

Simulation::Simulation(double delta_t, double sigma, LinkedCellContainer& container, ForceCalculation &calculation, Thermostat& thermostat, double averageVelo, Boundary &boundary, GravityForce &gravity) :
                        container(container),
                        forceCalculation(calculation),
                        thermostat(thermostat),
                        boundaryEnforcer(sigma, container, boundary.getDimensions(), boundary.getBoundaryTypes(), forceCalculation),
                        gravity(gravity),
                        delta_t(delta_t),
                        averageVelo(averageVelo) {}


Simulation::~Simulation() = default;

std::vector<Particle> Simulation::getParticles() {
    return container.getParticleVector();
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

void Simulation::applyGravity(Particle& p) {
    VectorDouble3 result = gravity.CalculateForce(p);
    p.setF(p.getFVector() + result);
}

void Simulation::runIteration() {
    // adjust temperature
    thermostat.updateState(container.getParticleVector());
    container.applyToAll([this](Particle& p){thermostat.updateTemperature(p);});
    thermostat.updateIteration();

    // calculate new x
    container.applyToAll([this](Particle& p) { calculateX(p); });

    // calculate new f
    container.applyToAll([](Particle& p) { setOldForce(p); });

    // apply boundary conditions
    container.applyToBoundary([this](Particle& p) { boundaryEnforcer.applyBoundaryConditionsForParticle(p); });

    container.applyToPairs([this](Particle& p1, Particle& p2) { calculateF(p1, p2); });

    container.deleteHaloParticles();

    container.applyToAll([this](Particle& p) { applyGravity(p); });
    // calculate new v
    container.applyToAll([this](Particle& p) { calculateV(p); });
}

void Simulation::setOldForce(Particle& p) {
    p.setOldF((p.getFVector()));
    p.setF(VectorDouble3());
}
