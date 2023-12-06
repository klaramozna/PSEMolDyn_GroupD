//
// Created by klara on 06.12.23.
//

#include "Thermostat.h"


void Thermostat::updateState(const std::vector<Particle> &particles) {
    double kineticEnergy = getKineticEnergy(particles);
    double updatedTemp = getTemperature(kineticEnergy, particles.size());
    currentTemperature = std::array<double, 3>{updatedTemp, updatedTemp, updatedTemp};
}
