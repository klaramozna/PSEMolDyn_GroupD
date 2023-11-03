//
// Created by rodff on 01.11.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMULATION_H
#define PSEMOLDYN_GROUPD_SIMULATION_H

#include <list>
#include "Particle.h"
#include "ParticleContainer.h"

class Simulation {
private:
    ParticleContainer container;
    double delta_t;

public:
    Simulation(double delta_t, ParticleContainer container);
    explicit Simulation(double delta_t);
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