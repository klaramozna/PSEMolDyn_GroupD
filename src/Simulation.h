//
// Created by rodff on 01.11.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMULATION_H
#define PSEMOLDYN_GROUPD_SIMULATION_H

#include <list>
#include "Particle.h"
#include "ParticleContainer.h"
#include "ForceCalculation.h"

class Simulation {
private:
    static constexpr double start_time = 0;

    ParticleContainer container;
    ForceCalculation &forceCalculation;

    double delta_t;
    /**
    * @brief calculate the velocity for all particles
    */
    void calculateV();

    /**
    * @brief calculate the position for all particles
    */
    void calculateX();

    /**
     * @brief calculate the force for all particles
    */
    void calculateF();
public:
    Simulation(double delta_t, ParticleContainer container, ForceCalculation &calculation);
    virtual ~Simulation();

    /**
     * @brief Returns a vector of particles.
     * @return Vector Container.
     */
    ParticleContainer& getParticles();

    /**
     * @brief run one iteration of the simulation, meaning position, force and then velocity
     */
    void runIteration();
};

#endif //PSEMOLDYN_GROUPD_SIMULATION_H