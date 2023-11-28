//
// Created by klara on 22.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CELL_H
#define PSEMOLDYN_GROUPD_CELL_H

#include <list>
#include <functional>
#include "Particle.h"

class Cell {
public:
    /**
     * @brief Possible types of cells, Inner means inside of boundary, Boundary means on the boundary, Halo means outside of the boundary.
     */

    using iterator_type = std::list<Particle>::iterator;

    /**
     * @brief Creates a Cell object, initializing it with the given particles and type
     * @param p The particles in the cell. Empty of no vector is given
     * @param t The type of the cell, Inner of no type is given.
     */
    explicit Cell(const std::list<Particle>& p = {}): particles{p}{};

    /**
     * @brief Returns an iterator pointing to the first particle.
     * @return Iterator pointing to the first particle.
     */
    iterator_type begin();

    /**
     * @brief Returns an iterator pointing after the last particle.
     * @return Iterator pointing after the last particle.
     */
    iterator_type end();

    /**
     * @brief Adds the given particle to the cell.
     * @param p The particle to be added.
     */
    void addParticle(const Particle& p);

    /**
     * @brief Deletes the given particle from the cell.
     * @param p The particle to be deleted.
     */
    void deleteParticle(const Particle& p);

    /**
     * @brief Applies the given function to each pair of particles within the cell.
     * @param function The function to be applied to the pairs.
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function);

    /**
     * @brief Applies the given function to all pairs between the cells (pairs (p1, p2) where p1 is from this cell and p2 from the parameter cell.). IMPORTANT: only the particles in this cell are modified.
     * @param cell The cell that this cell is supposed to interact with.
     * @param function Function to be applied to the pairs.
     */
    void interactWithCell(Cell cell, const std::function<void(Particle&, Particle&)>& function);

private:
    /**
     * @brief Stores the particles of the cell.
     */
    std::list<Particle> particles;

};




#endif //PSEMOLDYN_GROUPD_CELL_H
