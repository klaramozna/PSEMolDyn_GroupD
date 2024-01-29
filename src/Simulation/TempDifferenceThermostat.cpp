//
// Created by klara on 18.01.24.
//

#include "TempDifferenceThermostat.h"
#include "utils/MaxwellBoltzmannDistribution.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>

void TempDifferenceThermostat::updateTemperature(Particle &particle) {
    if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        VectorDouble3 tempDifference = particle.getVVector() - averageVelocity;
        particle.setV((beta * tempDifference) + averageVelocity);
    }
}

void TempDifferenceThermostat::updateState(const std::vector<Particle> &particles) {
    int numNonWallParticles = std::count_if(particles.begin(), particles.end(), [](Particle p){return !p.isWallParticle();});

    // Calculate average temperature
    averageVelocity = VectorDouble3{{0, 0, 0}};
    for(auto const & p : particles){
        if(!p.isWallParticle()){
            averageVelocity += p.getVVector();
        }
    }
    averageVelocity = (1.0/numNonWallParticles) * averageVelocity;

    // Modify particles to store the difference between the average velocity and current velocity
    std::vector<Particle> particleDiffs = particles;
    for(auto & p : particleDiffs){
        p.setV(p.getVVector() - averageVelocity);
    }

    // Calculate current temperature with the modified particles
    double kineticEnergy = getKineticEnergy(particleDiffs);
    currentTemperature = getTemperature(kineticEnergy, numNonWallParticles);
}

void TempDifferenceThermostat::initializeBrownianMotion(Particle &particle) const {
    if(particle.getM() <= 0){
        throw std::runtime_error("The given particle has a invalid weight / mass. Weight has to be strictly greater than zero.");
    }
    double factor = sqrt(initTemperature / particle.getM());
    VectorDouble3 resultVelocity = VectorDouble3(maxwellBoltzmannDistributedVelocity(factor, dim));
    particle.setV((particle.getVVector() - averageVelocity) + resultVelocity);
}
