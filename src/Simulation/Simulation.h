//
// Created by rodff on 01.11.23.
//

#ifndef PSEMOLDYN_GROUPD_SIMULATION_H
#define PSEMOLDYN_GROUPD_SIMULATION_H

#include <list>
#include "../Particles/Particle.h"
#include "../Particles/LinkedCellContainer.h"
#include "./Physics/ForceCalculation.h"
#include "./Physics/GravityForce.h"
#include "Thermostat.h"
#include "../Particles/Boundary.h"
#include "../Particles/BoundaryEnforcer.h"
#include "utils/ParallelizationStrategy.h"

#include <memory>

class Simulation {
private:
    static constexpr double start_time = 0;

    LinkedCellContainer& container;
    ForceCalculation &forceCalculation;
    Thermostat& thermostat;

    BoundaryEnforcer boundaryEnforcer;
    GravityForce gravity;

    double delta_t;

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
     /**
     * @brief applies the gravity
     */
    void applyGravity(Particle& p);


public:

    Simulation(double delta_t, double sigma, LinkedCellContainer& container, ForceCalculation &calculation, Thermostat& thermostat, double averageVelo, Boundary &boundary, GravityForce &gravity, bool applyBrownianMotion, int dim, ParallelizationStrategy parallelizationStrategy);

    virtual ~Simulation();

    /**
     * @brief Returns a vector of particles.
     * @return Vector Container.
     */
    std::vector<Particle> getParticles();

    /**
     * @brief run one iteration of the simulation, meaning position, force and then velocity
     */
    void runIteration();

    ParallelizationStrategy parallelizationStrategy;
};

#endif //PSEMOLDYN_GROUPD_SIMULATION_H