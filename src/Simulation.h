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
    ParticleContainer container;
    ForceCalculation* forceCalculation;
    double delta_t;

public:
    Simulation(double delta_t, ParticleContainer container, ForceCalculation *calculation);
    virtual ~Simulation();

    /**
     * @brief Returns a vector of particles.
     * @return Vector of particles.
     */
    std::vector<Particle>& getParticles();

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
};

#endif //PSEMOLDYN_GROUPD_SIMULATION_H