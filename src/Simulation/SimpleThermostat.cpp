//
// Created by klara on 07.12.23.
//

#include "SimpleThermostat.h"
#include <cmath>

void SimpleThermostat::updateTemperature(Particle &particle) {
    if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        particle.setV(beta * particle.getVVector());
    }
}
