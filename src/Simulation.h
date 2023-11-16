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
    double averageVelo;

    /**
    * @brief calculate the velocity of a particle
    */
    void calculateV(Particle& p) const;

    /**
    * @brief calculate the position of a particle
    */
    void calculateX(Particle& p) const;

    /**
     * @brief calculates the force between two particles, and updates the respective forces accordingly
    */
    void calculateF(Particle& p1, Particle& p2);

    /**
     * @brief updates the old force of a particle
     */
    static void setOldForce(Particle& p);

public:
    Simulation(double delta_t, ParticleContainer container, ForceCalculation &calculation, double averageVelo);
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