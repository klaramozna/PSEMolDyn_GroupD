//
// Created by klara on 27.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
#define PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H

#include "Boundary.h"

class CuboidBoundary : public Boundary {
public:
    /**
     * @brief Creates a CuboidBoundary object with the given parameters.
     * @param width Width of the cuboid boundary
     * @param height Height of the cuboid boundary.
     * @param depth Depth of the cuboid boundary.
     */
    CuboidBoundary(int width, int height, int depth): width(width), height(height), depth(depth){};

     /**
     * @brief Returns true, if the given particle is inside of or on the boundary, else false.
     * @param p The particle tested.
     * @return True, if the given particle is inside / on the boundary, else false.
     */
    bool isInside(const Particle& p) override;

    /**
     * @brief Returns width of boundary.
     * @return Width of boundary.
     */
    int getWidth() const{return width;};

    /**
     * @brief Returns height of boundary.
     * @return Height of boundary.
     */
    int getHeight() const{return height;};

    /**
     * @brief Returns depth of boundary.
     * @return Depth of boundary.
     */
    int getDepth() const{return depth;};

private:

    /**
     * @brief Width of the cuboid boundary.
     */
    int width;

    /**
     * @brief Height of the cuboid boundary.
     */
    int height;

    /**
     * @brief Depth of the cuboid boundary.
     */
    int depth;

};


#endif //PSEMOLDYN_GROUPD_CUBOIDBOUNDARY_H
