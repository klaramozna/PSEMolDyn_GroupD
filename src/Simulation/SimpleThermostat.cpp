//
// Created by klara on 07.12.23.
//

#include "SimpleThermostat.h"
#include <cmath>

void SimpleThermostat::updateTemperature(Particle &particle) {
    // Old version
    /*if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        particle.setV(beta * particle.getVVector());
    }*/

    // Version for task 4
    if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        particle.setV((beta * particle.getVVector()) + avgVelo);
    }

}
