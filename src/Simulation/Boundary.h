//
// Created by rodff on 22.11.23.
//

#pragma once

#include "../Particles/LinkedCellContainerStub.h"
#include "Physics/ForceCalculation.h"
#include <array>
#include <cmath>

/**
 * @file Boundary.h
 *
 * @brief Stores boundary information, such as type of boundary, starting point (3D vector) and dimensions in each axis,
 * and executes the boundary control according to the boundary type of a given "wall"
 * */



class Boundary {
public:
    const double sixthRootOf2 = std::pow(2.0, 1.0/6.0);

    /**
     * @brief Goes through all boundary particles and enforces boundary conditions according to the given boundary type
     * @param container LinkedCellContainer that implements the LinkedCellLogic
     * @param calculation Type of potential used to calculate particle interactions. Is useful for a specific
     * type of reflective boundary implementation
     *
     * */
    virtual void processBoundary(LinkedCellContainerStub &container, ForceCalculation &calculation) = 0;

    /**
     * @brief Constructor for a Boundary class
     * @param dimensions Vector containing the lengths of each "edge" along the axis
     * @param llc Left-Lower-Corner defining a point of reference for the boundaries
     * */
    Boundary(std::array<double,3> llc, std::array<double,3> dimensions) : llc{llc}, dimensions{dimensions} {};
protected:
    std::array<double,3> llc;
    std::array<double,3> dimensions;
};

