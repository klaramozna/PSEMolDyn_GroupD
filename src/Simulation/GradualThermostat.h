//
// Created by klara on 07.12.23.
//

#ifndef PSEMOLDYN_GROUPD_GRADUALTHERMOSTAT_H
#define PSEMOLDYN_GROUPD_GRADUALTHERMOSTAT_H

#include "Thermostat.h"

class GradualThermostat : public Thermostat{
public:

    /**
     * @brief Creates a GradualThermostat object with the given parameters.
     * @param initTemperature The temperature that particles can be (optionally) initialized later with.
     * @param targetTemperature The target temperature of the system.
     * @param cycleLength Number of iterations after which the thermostat is applied.
     * @param dim Dimension used. Has to be between 1 and 3.
     * @param maxChange The maximum change of temperature per iteration.
     */
    GradualThermostat(double initTemperature, double targetTemperature, int cycleLength, int dim, double maxChange): Thermostat{initTemperature, targetTemperature, cycleLength, dim}, maxChange{maxChange}{};

    /**
     * @brief Updates the temperature of the given particle, so that it is closer to the target value. The temperature change is not greater than maxChange.
     * @param particle The particle to be changed.
     */
    void updateTemperature(Particle& particle) override;

private:

    /**
     * @brief The maximum change of temperature per iteration.
     */
    double maxChange;
};


#endif //PSEMOLDYN_GROUPD_GRADUALTHERMOSTAT_H
