//
// Created by rodff on 01.11.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMULATION_H
#define PSEMOLDYN_GROUPD_SIMULATION_H

#include <list>
#include "Particle.h"

class Simulation {
private:
    std::list<Particle> particles;
    double delta_t;

public:
    Simulation(double delta_t);
    Simulation(double delta_t, std::list<Particle> particles);
    virtual ~Simulation();


    /**
     * Getter for list of particles
     */
    std::list<Particle>& getParticles();

    /**
    * calculate the velocity for all particles
    */
    void calculateV();

    /**
    * calculate the position for all particles
    */
    void calculateX();

    /**
     * calculate the force for all particles
    */
    void calculateF();
};

#endif //PSEMOLDYN_GROUPD_SIMULATION_H