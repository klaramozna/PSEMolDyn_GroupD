//
// Created by klara on 18.01.24.
//

#include "TempDifferenceThermostat.h"
#include <cmath>

void TempDifferenceThermostat::updateTemperature(Particle &particle) {
    if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        VectorDouble3 tempDifference = particle.getVVector() - averageVelocity;
        particle.setV((beta * tempDifference) + averageVelocity);
    }
}

void TempDifferenceThermostat::updateState(const std::vector<Particle> &particles) {
    // Calculate average temperature
    averageVelocity = VectorDouble3{{0, 0, 0}};
    for(auto const & p : particles){
        averageVelocity += p.getVVector();
    }
    averageVelocity = (1.0/particles.size()) * averageVelocity;

    // Modify particles to store the difference between the average velocity and current velocity
    std::vector<Particle> particleDiffs = particles;
    for(auto & p : particleDiffs){
        p.setV(p.getVVector() - averageVelocity);
    }

    // Calculate current temperature with the modified particles
    double kineticEnergy = getKineticEnergy(particleDiffs);
    currentTemperature = getTemperature(kineticEnergy, particleDiffs.size());
}
