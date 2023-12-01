//
// Created by klara on 27.11.23.
//

#ifndef PSEMOLDYN_GROUPD_BOUNDARY_H
#define PSEMOLDYN_GROUPD_BOUNDARY_H


#include <array>
#include "Particle.h"

class Boundary {
public:
    /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
    virtual bool isInside(const Particle& p) = 0;

    /**
     * @brief Returns true, if the given particle is outside of the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is outside of boundary, else false.
     */
    virtual bool isOutside(const Particle& p) final;

    /**
     * @brief Destroys a boundary object
     */
    virtual ~Boundary() = default;
};


#endif //PSEMOLDYN_GROUPD_BOUNDARY_H
