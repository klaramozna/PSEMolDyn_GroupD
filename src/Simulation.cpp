/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include "Simulation.h"
#include "VectorDouble.h"
#include "Particle.h"

#include <complex>
#include <utility>

Simulation::Simulation(double delta_t) {
    this->delta_t = delta_t;
}

Simulation::Simulation(double delta_t, std::list<Particle> particles) {
    this->delta_t = delta_t;
    this->particles = std::move(particles);
}

Simulation::~Simulation() = default;

std::list<Particle>& Simulation::getParticles() {
    return this->particles;
}

void Simulation::calculateF() {
    std::list<Particle>::iterator iterator;
    iterator = this->particles.begin();

    for (auto &p1: this->particles) {
        p1.setOldF(p1.getFVector());
        VectorDouble f_i(3);
        for (auto &p2: this->particles) {
            if(!(p2 == p1)){
                f_i += ((p1.getM() * p2.getM()) / pow((p1.getXVector() - p2.getXVector()).getL2Norm(), 3)) * (p2.getXVector() - p1.getXVector());
            }
        }
        p1.setF(f_i);
    }
}

void Simulation::calculateV() {
    for (auto &p: this->particles) {
        VectorDouble v_i = p.getVVector() + (this->delta_t / (2. * p.getM()) * (p.getOldFVector() + p.getFVector()));
        p.setV(v_i);
    }
}

void Simulation::calculateX() {
    for (auto &p: this->particles) {
        VectorDouble x_i = p.getXVector() + this->delta_t * p.getVVector()
                           + ((this->delta_t * this->delta_t) / (2. * p.getM())) * p.getOldFVector();
        p.setX(x_i);
    }
}
