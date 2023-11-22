//
// Created by klara on 22.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H


#include "ParticleContainer.h"

class LinkedCellContainer : public ParticleContainer{
public:
    /**
     * @brief Creates a LinkedCellContainer object using the given parameters.
     * @param boundaryCorner Contains the x, y and z coordinate (in this order) of the lower, left, front corner of the boundary.
     * @param meshSize Width / length / height of each cell.
     * @param n1 Number of cells in the x direction.
     * @param n2 Number of cells in the y direction.
     * @param n3 Number of cells in the z direction.
     * @param particles The particles to be added to the container.
     */
    LinkedCellContainer(std::array<double, 3> boundaryCorner, double meshSize, int n1, int n2, int n3, std::vector<Particle> particles = {});

    /**
     * @brief Adds the given particle to the container.
     * @param p The particle to be added.
     */
    void addParticle(const Particle& p) override;

    /**
     * @brief Returns the number of particles in the container.
     * @return The number of particles in the container.
     */
    size_t getSize() override;

    /**
     * @brief Applies the given function to all particles.
     * @param function Function that is applied to each particle.
     */
    void applyToAll(const std::function<void(Particle&)>& function) override;

    /**
     * @brief Applies the given function to pairs of particles in neighbouring cells according to the linked-cell algorithm.
     * @param function The function to be applied to each pair.
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;

    /**
     * @brief Returns a vector of all particles in the container.
     * @return The vector with the particles of the container.
     */
    std::vector<Particle>& getParticleVector() override;

    /**
     * @brief Applies the given function to each particle in the boundary
     * @param function
     */
    void applyToBoundary(const std::function<void(Particle(&))>& function);

    /**
     * @brief Deletes all particles, for which the given function returns true.
     * @param function The function that decides if a particle should be deleted (deleted if true, otherwise not deleted).
     */
    void deleteParticlesIf(const std::function<bool(Particle)>& function);

    /**
     * @brief Deletes particles outside of the boundary from the container.
     */
    void deleteHaloParticles();


};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H
