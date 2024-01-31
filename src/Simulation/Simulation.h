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
#include "./Physics/HardcodedPullForce.h"
#include "Thermostat.h"
#include "../Particles/Boundary.h"
#include "../Particles/BoundaryEnforcer.h"
#include "utils/ParallelizationSpec.h"
#include "FakeThermostat.h"

/** Related to IO, Benchmarking **/
#include "../IO/input/SimParameters.h"
#include "../Benchmark.h"
#include "../IO/Logger.h"
#include "../IO/output/outputWriter/CheckpointWriter.h"
#include "../IO/output/outputWriter/XYZWriter.h"
#include "../IO/output/outputWriter/VTKWriter.h"

#include <memory>

class Simulation {
private:
    static constexpr double start_time = 0;
    double current_time;

    LinkedCellContainer& container;
    ForceCalculation &forceCalculation;
    Thermostat& thermostat;

    BoundaryEnforcer boundaryEnforcer;
    GravityForce gravity;
    HardcodedPullForce pullForce;

    SimParameters simParameters;
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
    /**
     * @brief applies harmonic Forces (for membrane)
     */
    void applyHarmonicForces(Particle& p);

    void applyPullForce(Particle& p);


    double getCurrentTime() {
        return current_time;
    }

     /**
     * @brief run one iteration of the simulation, meaning position, force and then velocity
     */
    void runIteration();



public:
    Simulation(SimParameters& simParameters, LinkedCellContainer& container, ForceCalculation &calculation, Thermostat& thermostat, Boundary &boundary, GravityForce &gravity, HardcodedPullForce &hardcodedPullForce);

    virtual ~Simulation();

    /**
     * @brief Returns a vector of particles.
     * @return Vector Container.
     */
    std::vector<Particle> getParticles();

    /**
     * @brief run the simulation
     */
    void runSimulation();
};

#endif //PSEMOLDYN_GROUPD_SIMULATION_H