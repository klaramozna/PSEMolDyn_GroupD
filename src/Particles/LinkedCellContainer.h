//
// Created by klara on 22.11.23.
//

#pragma once

#include "ParticleContainer.h"
#include "CuboidBoundary.h"
#include "Cell.h"

#include "BoundaryCellsIterator.h"

class LinkedCellContainer : public ParticleContainer {
public:
    /**
     * @brief Creates a LinkedCellContainer object using the given parameters.
     * @param boundary Cuboid boundary to be used for the container.
     * @param cutoffRadius Radius in which the particles affect each other.
     * @param particles The particles to be added to the container.
     */
    LinkedCellContainer(CuboidBoundary boundary, double cutoffRadius, const std::vector<Particle>& particles = {});

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
     * @brief Applies the given function to pairs of particles in neighbouring cells within the cutoff radius.
     * @param function The function to be applied to each pair, that does not change the position of the particles.
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;

    /**
     * @brief Returns a vector of all particles in the container.
     * @return The vector with the particles of the container.
     */
    std::vector<Particle> getParticleVector() override;

    /**
     * @brief Applies the given function to each particle in the boundary
     * @param function
     */
    void applyToBoundary(const std::function<void(Particle(&))>& function);

    /**
     * @brief Deletes particles outside of the boundary from the container.
     */
    void deleteHaloParticles();

    /**
     * @brief Only for testing purposes. Dont use.
     * @return Returns the vector of Cells.
     */
    std::vector<Cell> getCells();

    /**
    * @brief Returns an iterator pointing to the beginning of the boundary cells.
    * @return BoundaryCellIterator pointing to the beginning of the boundary cells.
    */
    auto beginBoundaryCells() {
        return BoundaryCellIterator(boundaryCells_ptr, 0);
    }

    /**
     * @brief Returns an iterator pointing to the end of the boundary cells.
     * @return BoundaryCellIterator pointing to the end of the boundary cells.
     */
    auto endBoundaryCells() {
        return BoundaryCellIterator(boundaryCells_ptr, boundaryCells_ptr.size());
    }

private:

    /**
     * @brief Vectors containing all cells, going from the lower left front corner (first increasing z, then y then x).
     */
    std::vector<Cell> grid;

    /**
     * @brief Vector containing boundary cells
     */
    std::vector<Cell> boundaryCells;

    /**
     * @brief Reference to BoundaryControl
     * */
     CuboidBoundary& boundary;


    /**
     * @brief Specifies the radius, in which the particles affect each other.
     */
    double cutoffRadius;

    /**
     * @brief Stores number of cells for each dimension
     */
    std::array<int,3> nc;

    /**
     * @brief Stores the shift of the grid from the (0, 0, 0) corner to the left lower direction.
     */
    std::array<double, 3> gridShift;

    double cellSize;

    /**
     * @brief Puts all particles in their correct cells after a change in position.
     */
    void updateCells();

    /**
     * @brief Number of particles in the container.
     */
    size_t size;

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

    /**
     * @brief Returns a the index in the grid of a cell with the given position,
     * @param x X position of the cell.
     * @param y Y position of the cell.
     * @param z Z position of the cell.
     * @return Grid index of the cell with the given coordinates.
     */
    int getGridIndex(int x, int y, int z) const;

    /**
     * @brief Returns true, if the cell with the position (x, y, z) is within the cutoff radius of the given particle.
     * @param p The particle for which the distance is calculated.
     * @param x X position of the cell.
     * @param y Y position of the cell.
     * @param z Z position of the cell.
     * @return True, if the cell is within the cutoff radius of particle p, false otherwise
     */
    bool cellWithinRadius(const Particle& p, int x, int y, int z);

    /**
     * @brief Returns true if the distance (euclidian) between the two particles is smaller or equal to the cutoff radius.
     * @param p1 The first particle.
     * @param p2 The second particle.
     * @return True if the distance is smaller or equal to the cutoff radius, false otherwise.
     */
    bool particleWithinCutoff(const Particle& p1, const Particle& p2) const;

    /**
     * @brief Returns the index in the grid of the given particle.
     * @param p The particle, for which the index is being calculated.
     * @return The correct index in the grid vector.
     */
    int getParticleIndex(const Particle& p);


    /**
     * @brief Determines whether a (x,y,z) entry in a 3D array leads to a boundary cell
     * according to the number of cells in the container in each axis
     * @param x Integer defining the 1st entry of the multi-index
     * @param y Integer defining the 2nd entry of the multi-index
     * @param z Integer defining the 3rd entry of the multi-index
     */
     bool isBoundaryCell(int x, int y, int z);

     /**
      * @brief Returns true if the given particle is positioned outside of the grid.
      * @param p The particle to be evaluated.
      * @return True rue if the given particle is positioned outside of the grid, otherwise false.
      */
     bool particleOutOfGrid(const Particle& p);
};
