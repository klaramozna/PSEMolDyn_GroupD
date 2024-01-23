 //
// Created by klara on 18.01.24.
//

#ifndef PSEMOLDYN_GROUPD_TEMPDIFFERENCETHERMOSTAT_H
#define PSEMOLDYN_GROUPD_TEMPDIFFERENCETHERMOSTAT_H

#include "Thermostat.h"


 class TempDifferenceThermostat : public Thermostat{
public:

     /**
      * @brief Creates a TempDifferenceThermostat object based on the given parameters.
      * @param initTemperature The temperature that particles can be (optionally) initialized later with.
      * @param targetTemperature The target temperature of the system.
      * @param cycleLength Number of iterations after which the thermostat is applied.
      * @param dim Dimension used. Has to be between 1 and 3.
      */
     TempDifferenceThermostat(double initTemperature, double targetTemperature, int cycleLength, int dim): Thermostat{initTemperature, targetTemperature, cycleLength, dim}{};

     /**
      * @brief Uses simple velocity scaling of the difference between the particle's velocity and the average velocity to adjust the temperature of the given particle to the desired level (targetTemperature).
      * @param particle The particle to be changed.
      */
     void updateTemperature(Particle &particle) override;

     /**
      * @brief Updates state of the thermostat.
      * @param particles Particles in the current iteration
      */
     void updateState(const std::vector<Particle>& particles) override;

private:

    /**
     * @brief Average velocity of the particles.
     */
    VectorDouble3 averageVelocity{};

};


#endif //PSEMOLDYN_GROUPD_TEMPDIFFERENCETHERMOSTAT_H
