//
// Created by klara on 22.11.23.
//

#pragma once

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
     * @brief Returns true if the given particle is contained in this cell.
     * @param p The particle to be tested.
     * @return True if the particle is in this cell, false otherwise.
     */
    bool contains(const Particle& p);

private:
    /**
     * @brief Stores the particles of the cell.
     */
    std::list<Particle> particles;

};
