//
// Created by klara on 22.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CELL_H
#define PSEMOLDYN_GROUPD_CELL_H

#include "Particle.h"

class Cell {
public:
    /**
     * @brief Possible types of cells, Inner means inside of boundary, Boundary means on the boundary, Halo means outside of the boundary.
     */
    enum Type {Inner, Halo, Boundary};

    using iterator_type = std::vector<Particle>::iterator;

    /**
     * @brief Creates a Cell object, initializing it with the given particles and type
     * @param p The particles in the cell. Empty of no vector is given
     * @param t The type of the cell, Inner of no type is given.
     */
    explicit Cell(const std::vector<Particle>& p = {}, Type t = Inner);

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
     * @brief Returns the type of the boundary: Inner, Boundary or Halo.
     * @return The type of the boundary.
     */
    Type getType();

    /**
     * @brief Sets the type of the cell according to the given parameter.
     * @param type Type of the cell.
     */
    void setType(Type t);

private:
    /**
     * @brief Stores the particles of the cell.
     */
    std::vector<Particle> particles;

    /**
     * @brief Type of the cell (Boundary, Halo or Inner).
     */
    Type type;

};


#endif //PSEMOLDYN_GROUPD_CELL_H
