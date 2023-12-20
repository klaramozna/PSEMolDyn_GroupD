//
// Created by klara on 07.12.23.
//

#include "SimpleThermostat.h"
#include <cmath>
#include "../utils/VectorDouble3.h"

void SimpleThermostat::updateTemperature(Particle &particle) {
    if(currentIteration % cycleLength == 0){
        double beta = sqrt(targetTemperature / currentTemperature);
        particle.setV(scaleSIMD(beta, particle.getVVector()));
    }
}
