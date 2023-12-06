//
// Created by klara on 06.12.23.
//

#include "Thermostat.h"
#include <cmath>
#include "utils/VectorDouble3.h"


void Thermostat::updateState(const std::vector<Particle> &particles) {
    double kineticEnergy = getKineticEnergy(particles);
    currentTemperature = getTemperature(kineticEnergy, particles.size());
}

void Thermostat::initializeBrownianMotion(Particle &particle) const {
    double factor = sqrt(initTemperature / particle.getM());
    std::array<double, 3> resultVelocity = maxwellBoltzmannDistributedVelocity(factor, dim);
    particle.setV(resultVelocity[0], resultVelocity[1], resultVelocity[2]);
}

double Thermostat::getKineticEnergy(const std::vector<Particle> &particles) const {
    double sum = 0;
    VectorDouble3 v{};
    for(auto & particle : particles){
        sum += (particle.getM() / 2) * getDotProduct(particle.getVVector(), particle.getVVector());
    }
    return sum;
}

double Thermostat::getTemperature(double kineticEnergy, int numParticles) const {
    return (kineticEnergy * 2) / (dim * numParticles);
}
