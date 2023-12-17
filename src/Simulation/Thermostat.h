//
// Created by klara on 06.12.23.
//

#ifndef PSEMOLDYN_GROUPD_THERMOSTAT_H
#define PSEMOLDYN_GROUPD_THERMOSTAT_H

#include "../Particles/Particle.h"

class Thermostat {
public:
    /**
     * @brief Creates a thermostat object based on the given parameters.
     * @param initTemperature The temperature that particles can be (optionally) initialized later with.
     * @param targetTemperature The target temperature of the system.
     * @param cycleLength Number of iterations after which the thermostat is applied.
     * @param dim Dimension used. Has to be between 1 and 3.
     */
    Thermostat(double initTemperature, double targetTemperature, int cycleLength, int dim): initTemperature{initTemperature}, currentTemperature{0}, targetTemperature{targetTemperature}, dim{dim}, cycleLength{cycleLength}, currentIteration{0}{}

    Thermostat() = default;

    /**
     * @brief Changes the temperature of the given particle according to the type of the thermostat.
     * @param particle The particle to be changed.
     */
    virtual void updateTemperature(Particle& particle) = 0;

    /**
     * @brief Updates the current temperature based on how the particles changed. Needs to be called whenever the particles change.
     * @param particles The current state of the particles.
     */
    void updateState(const std::vector<Particle>& particles);

    /**
     * @brief Needs to be called exactly once per iteration, to help the thermostat keep track of the iterations. Needs to be called after calling updateTemperature.
     */
    void updateIteration();

    /**
     * @brief Sets the velocity of the particle to a value according to the brownian motion.
     * @param particle The particle to which brownian motion is being applied.
     */
    void initializeBrownianMotion(Particle& particle) const;

    /**
     * @brief Destroys the thermostat object.
     */
    virtual ~Thermostat() = default;

    /**
     * @brief Returns the current temperature of the system.
     * @return Current temperature.
     */
    double getCurrentTemperature();

private:

    /**
     * @brief The temperature that particles should be initialized with.
     */
    double initTemperature;

    /**
     * @brief Dimension used. Has to be between 1 and 3
     */
    int dim;

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

protected:

    /**
     * @brief The number of the current iteration.
     */
    int currentIteration;

    /**
     * @brief Number of iterations after which the thermostat is applied.
     */
    int cycleLength;

    /**
     * @brief Current temperature of the system.
     */
    double currentTemperature;

    /**
     * @brief Target temperature of the system.
     */
    double targetTemperature;


};


#endif //PSEMOLDYN_GROUPD_THERMOSTAT_H
