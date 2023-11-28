//
// Created by klara on 22.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H


#include "ParticleContainer.h"
#include "Cell.h"
#include "CuboidBoundary.h"

class LinkedCellContainer : public ParticleContainer{
public:
    /**
     * @brief Creates a LinkedCellContainer object using the given parameters.
     * @param boundary Cuboid boundary to be used for the container.
     * @param cutoffRadius Radius in which the particles affect each other.
     * @param particles The particles to be added to the container.
     */
    LinkedCellContainer(CuboidBoundary boundary, double cutoffRadius, std::vector<Particle> particles = {});

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
     * @brief Deletes particles outside of the boundary from the container.
     */
    void deleteHaloParticles();

private:

    /**
     * @brief Vectors containing all cells, going from the lower left front corner (first increasing z, then y then x).
     */
    std::vector<Cell> grid;

    /**
     * @brief Specifies the radius, in which the particles affect each other.
     */
    double cutoffRadius;

    /**
     * @brief Number of cells in the x-direction.
     */
    int numCellsX;

    /**
     * @brief Number of cells in the y-direction.
     */
    int numCellsY;

    /**
     * @brief Number of cells in the z-direction.
     */
    int numCellsZ;

    /**
     * @brief Puts all particles in their correct cells after a change in position.
     */
    void updateCells();

    /**
     * @brief Number of particles in the container.
     */
    size_t size;

    /**
     * @brief Puts particles from the given vector to their correct cells.
     * @param particles The particles to be put in their cells.
     */
    void putParticlesToCells(const std::vector<Particle>& particles);

    /**
     * @brief Returns the index of the cell that the given particle belongs to based on its position.
     * @param p The particle that the index is being calculated based on.
     * @return Index of the correct cell in the grid vector.
     */
    int getCellIndex(const Particle& p) const;

    /**
     * @brief Deletes the given particle from the cell with the index oldCell and adds it to the cell with the index newCell
     * @param p1 Particle to be moved.
     * @param oldCell Index of the cell the particle is being moved from.
     * @param newCell Index of the cell the particle is being moved to.
     */
    void moveParticle(const Particle& p1, int oldCell, int newCell);

    /**
     * @brief Returns true if the given particle is it's correct cell.
     * @param p The particle to be tested.
     * @param currentIndex The index of the grid the particle is currently in.
     * @return True if the particle is in the correct cell, false otherwise.
     */
    bool isInCorrectCell(const Particle& p, int currentIndex);
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINER_H
