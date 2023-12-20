//
// Created by rodff on 14.12.23.
//

#ifndef PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H
#define PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H

#include "LinkedCellContainer.h"

#include "../Simulation/Physics/ForceCalculation.h"

#include "../utils/BoundaryTypes.h"
#include "../utils/BoundaryDirection.h"
#include "../utils/Constants.h"

class BoundaryEnforcer {
public:
     /**
     * @brief Constructor for BoundaryEnforcer.
     *
     * @param sigma: Interaction distance parameter.
     * @param container: Reference to the LinkedCellContainer managing particle positions.
     * @param dimensions: Array representing the dimensions of the simulation domain.
     * @param boundaryTypes: Array representing the boundary types for each direction.
     * @param fc: Reference to the ForceCalculation object for calculating particle forces.
     */
    BoundaryEnforcer(double sigma, LinkedCellContainer &container, std::array<double,3> dimensions, std::array<BoundaryType, 6> boundaryTypes, ForceCalculation &fc);

     /**
     * @brief Applies boundary conditions to a particle.
     *
     * @param particle: Reference to the particle to which boundary conditions are applied.
     */
    void applyBoundaryConditionsForParticle(Particle &particle);
private:
    LinkedCellContainer &container;

    // Array representing the dimensions of the simulation domain.
    std::array<double,3> dimensions;

    // Array representing the boundary types for each direction.
    std::array<BoundaryType, 6> boundaryTypes;

    double sigma;
    ForceCalculation &fc;

    /**
     * @brief Applies reflective force to a particle based on its boundaries.
     *
     * @param p: Reference to the particle to which reflective force is applied.
     * @param boundaryofParticle: Vector of BoundaryDirection indicating the particle's boundaries.
     */
    void applyReflectiveForce(Particle &p, std::vector<BoundaryDirection> boundaryofParticle);

    /**
     * @brief Applies periodic boundary conditions to a particle.
     *
     * @param p: Reference to the particle to which periodic boundary conditions are applied.
     */
    void applyPeriodicBoundary(Particle &p);

    /**
     * @brief Gets the boundary directions of a particle based on its position.
     *
     * @param particle: Reference to the particle for which boundary directions are determined.
     * @return Vector of BoundaryDirection indicating the particle's boundaries.
     */
    std::vector<BoundaryDirection> getBoundariesOfParticle(Particle &particle);

    /**
     * @brief Checks if a given position corresponds to a particle in the halo region.
     *
     * @param x: X-coordinate of the position.
     * @param y: Y-coordinate of the position.
     * @param z: Z-coordinate of the position.
     * @return True if the position is in the halo region; otherwise, false.
     */
    bool isHaloParticle(double x, double y, double z);
};


#endif //PSEMOLDYN_GROUPD_BOUNDARYENFORCER_H
