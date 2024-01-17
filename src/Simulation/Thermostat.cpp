//
// Created by klara on 06.12.23.
//

#include "Thermostat.h"
#include <cmath>
#include "../utils/VectorDouble3.h"
#include <stdexcept>
#include "../utils/MaxwellBoltzmannDistribution.h"


void Thermostat::updateState(const std::vector<Particle> &particles) {

    // for task 4
    VectorDouble3 avgVelo{{0, 0, 0}};
    for(auto const & p : particles){
        avgVelo += p.getVVector();
    }

    avgVelo = (1.0/particles.size()) * avgVelo;
    this->particles = particles;
    for(auto & p : this->particles){
        p.setV(p.getVVector() - avgVelo);
    }

    // Original version
    double kineticEnergy = getKineticEnergy(particles);
    currentTemperature = getTemperature(kineticEnergy, particles.size());

}

void Thermostat::initializeBrownianMotion(Particle &particle) const {
    if(particle.getM() <= 0){
        throw std::runtime_error("The given particle has a invalid weight / mass. Weight has to be strictly greater than zero.");
    }
    double factor = sqrt(initTemperature / particle.getM());
    VectorDouble3 resultVelocity = VectorDouble3(maxwellBoltzmannDistributedVelocity(factor, dim));
    particle.setV(particle.getVVector() + resultVelocity);
}

double Thermostat::getKineticEnergy(const std::vector<Particle> &particles) const {
    double sum = 0;
    VectorDouble3 v{};
    for(auto & particle : particles){
        sum += (particle.getM() * getDotProduct(particle.getVVector(), particle.getVVector())) / 2.0;
    }
    return sum;
}

double Thermostat::getTemperature(double kineticEnergy, int numParticles) const {
    return (kineticEnergy * 2) / (dim * numParticles);
}

double Thermostat::getCurrentTemperature() {
    return currentTemperature;
}

void Thermostat::updateIteration() {
    currentIteration++;
}

