//
// Created by klara on 07.12.23.
//

#include "GradualThermostat.h"
#include "cmath"

void GradualThermostat::updateTemperature(Particle &particle) {
    if(currentIteration % cycleLength == 0){

        // Check if the temperature change to target temperature exceeds the maximum change per iteration and adjust accordingly.
        double iterationTempTarget = targetTemperature;
        if(fabs(targetTemperature - currentTemperature) > maxChange){
            iterationTempTarget = targetTemperature >= currentTemperature ? currentTemperature + maxChange : currentTemperature - maxChange;
        }
        double beta = sqrt(iterationTempTarget / currentTemperature);
        particle.setV(beta * particle.getVVector());
    }
    currentIteration++;
}
