//
// Created by rodff on 01.11.23.
//

#pragma once

#include <list>
#include <memory>

// Particle imports
#include "../Particles/ParticleContainer.h"
#include "../Particles/Particle.h"
#include "../Particles/CuboidBoundary.h"

// Physics imports
#include "Physics/ForceCalculation.h"

class Simulation {
private:
    static constexpr double start_time = 0;

    std::shared_ptr<ParticleContainer> container;
    ForceCalculation &forceCalculation;
    CuboidBoundary &boundary;

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
    Simulation(double delta_t, std::shared_ptr<ParticleContainer> container, ForceCalculation &calculation, double averageVelo, CuboidBoundary &boundary);
    ~Simulation() = default;

    /**
     * @brief Returns a vector of particles.
     * @return Vector Container.
     */
    std::vector<Particle> getParticles();

    /**
     * @brief run one iteration of the simulation, meaning position, force and then velocity
     */
    void runIteration();
};