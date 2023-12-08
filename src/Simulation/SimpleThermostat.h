//
// Created by klara on 07.12.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H
#define PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H

#include  "Thermostat.h"

class SimpleThermostat : public Thermostat{
public:

    /**
     * @brief Creates a SimpleThermostat object based on the given parameters.
     * @param initTemperature The temperature that particles can be (optionally) initialized later with.
     * @param targetTemperature The target temperature of the system.
     * @param cycleLength Number of iterations after which the thermostat is applied.
     * @param dim Dimension used. Has to be between 1 and 3.
     */
    SimpleThermostat(double initTemperature, double targetTemperature, int cycleLength, int dim): Thermostat{initTemperature, targetTemperature, cycleLength, dim}{};

    /**
     * @brief Uses simple velocity scaling to adjust the temperature of the given particle to the desired level (targetTemperature).
     * @param particle The particle to be changed.
     */
    void updateTemperature(Particle &particle) override;
};


#endif //PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H
