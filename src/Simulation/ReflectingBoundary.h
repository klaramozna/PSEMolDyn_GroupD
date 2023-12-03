//
// Created by rodff on 22.11.23.
//

#pragma once

#include "Boundary.h"

class ReflectingBoundary : public Boundary {
public:
    void processBoundary(LinkedCellContainer &container) override = 0;
protected:

    /**
     * @brief Returns coordinate of orthogonal projection of the particles position to neighbouring boundary cells
     * @param particle Particle
     * */

     // Still needs implementation
     std::vector<std::array<double,3>> findOppositeParticles(Particle &particle) {};
};

