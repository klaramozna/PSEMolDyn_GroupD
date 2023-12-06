//
// Created by klara on 06.12.23.
//

#ifndef PSEMOLDYN_GROUPD_THERMOSTAT_H
#define PSEMOLDYN_GROUPD_THERMOSTAT_H


#include "Particles/Particle.h"
#include "utils/MaxwellBoltzmannDistribution.h"

class Thermostat {
public:
    /**
     * @brief Creates a thermostat object based on the given parameters.
     * @param initTemperature The temperature that particles can be (optionally) initialized later with.
     * @param targetTemperature The target temperature of the system.
     * @param cycleLength Number of iterations after which the thermostat is applied.
     * @param dim Dimension used. Has to be between 1 and 3.
     */
    Thermostat(double initTemperature, double targetTemperature, int cycleLength, int dim): initTemperature{initTemperature}, currentTemperature{0}, targetTemperature{targetTemperature}, dim{dim}, cycleLength{cycleLength}, currentIteration{0}{};

    /**
     * @brief Changes the temperature of the given particle according to the type of the thermostat.
     * @param particle The particle to be changed.
     */
    virtual void updateTemperature(Particle& particle) = 0;

    /**
     * @brief Needs to be called in every iteration before updating temperature. Updates the current temperature based on how the particles changed.
     * @param particles The current state of the particles.
     */
    void updateState(const std::vector<Particle>& particles);

    /**
     * @brief Sets the velocity of the particle to a value according to the brownian motion.
     * @param particle The particle to which brownian motion is being applied.
     */
    void initializeBrownianMotion(Particle& particle) const;

    /**
     * @brief Destroys the thermostat object.
     */
    virtual ~Thermostat() = default;

private:

    /**
     * @brief The temperature that particles should be initialized with.
     */
    double initTemperature;

    /**
     * @brief Current temperature of the system.
     */
    double currentTemperature;

    /**
     * @brief Target temperature of the system.
     */
    double targetTemperature;

    /**
     * @brief Dimension used. Has to be between 1 and 3
     */
    int dim;

    /**
     * @brief Number of iterations after which the thermostat is applied.
     */
    int cycleLength;

    /**
     * @brief The number of the current iteration.
     */
    int currentIteration;

    /**
     * @brief Calculates the kinetic energy of the given particles.
     * @param particles The particles that the energy is supposed to be calculated with.
     * @return The kinetic energy of all particles.
     */
    double getKineticEnergy(const std::vector<Particle>& particles) const;

    /**
     * @brief Calculates the temperature based on the kinetic energy.
     * @param kineticEnergy Kinetic energy of the system.
     * @param numParticles Number of particles.
     * @return The calculated temperature.
     */
    double getTemperature(double kineticEnergy, int numParticles) const;
};


#endif //PSEMOLDYN_GROUPD_THERMOSTAT_H
