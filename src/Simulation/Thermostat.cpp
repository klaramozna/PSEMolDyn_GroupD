//
// Created by klara on 06.12.23.
//

#include "Thermostat.h"
#include <cmath>
#include "../utils/VectorDouble3.h"
#include <stdexcept>
#include "../utils/MaxwellBoltzmannDistribution.h"
#include <algorithm>


void Thermostat::updateState(const std::vector<Particle> &particles) {
    double kineticEnergy = getKineticEnergy(particles);
    int numNonWallParticles = std::count_if(particles.begin(), particles.end(), [](Particle p){return !p.isWallParticle();});
    currentTemperature = getTemperature(kineticEnergy, numNonWallParticles);
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
        if(!particle.isWallParticle()){
            sum += (particle.getM() * getDotProduct(particle.getVVector(), particle.getVVector())) / 2.0;
        }
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

