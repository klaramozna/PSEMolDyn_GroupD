//
// Created by klara on 07.12.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H
#define PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H

#include  "Thermostat.h"

class SimpleThermostat : public Thermostat{
public:

    /**
     * @brief Uses simple velocity scaling to adjust the temperature of the given particle to the desired level (targetTemperature).
     * @param particle The particle to be changed.
     */
    void updateTemperature(Particle &particle) override;
};


#endif //PSEMOLDYN_GROUPD_SIMPLETHERMOSTAT_H
