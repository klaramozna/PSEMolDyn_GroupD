//
// Created by rodff on 08.12.23.
//

#include "ReflectiveBoundary.h"
#include <cmath>
#include <iostream>

void ReflectiveBoundary::applyBoundaryToParticle(Particle &p) {
    std::array<double, 3> particlePosition = p.getX();
    std::array<double, 3> boundaryDimensions = this->getDimensions();

    std::array<double, 3> opposingParticlePosition = particlePosition;

    // Check x-axis
    if (boundaryDimensions[0] - particlePosition[0] < cellSize && boundaryDimensions[0] - particlePosition[0] > 0) {
        opposingParticlePosition[0] += 2*std::abs(particlePosition[0] - boundaryDimensions[0]);
    } else if (particlePosition[0] < cellSize && particlePosition[0] > 0) {
        opposingParticlePosition[0] -= 2*particlePosition[0];
    }

    // Check y-axis
    if (boundaryDimensions[1] - particlePosition[1] < cellSize && boundaryDimensions[1] - particlePosition[1] > 0) {
        opposingParticlePosition[1] += 2 * std::abs(particlePosition[1] - boundaryDimensions[0]);
    } else if (particlePosition[1] < cellSize && particlePosition[1] > 0) {
        opposingParticlePosition[1] -= 2 *particlePosition[1];
    }

    // Check z-axis (if it's not a 2D <-> z = 1.0)
    if (boundaryDimensions[2] - particlePosition[2] < cellSize && boundaryDimensions[2] - particlePosition[2] > 0) {
        opposingParticlePosition[2] += 2 * std::abs(particlePosition[2] - boundaryDimensions[2]);
    } else if (particlePosition[2] < cellSize && particlePosition[2] > 0) {
        opposingParticlePosition[2] -= 2 *particlePosition[2];
    }

    if (getDistance(VectorDouble3(particlePosition), VectorDouble3(opposingParticlePosition)) <= sixthRootOfTwo * sigma) {
        auto opposingParticle = Particle(opposingParticlePosition, {0.0, 0.0, 0.0}, p.getM());
        auto result = fc.CalculateForces(p, opposingParticle);
        p.setF(p.getFVector() + result);
    }
}

ReflectiveBoundary::ReflectiveBoundary(double width, double height, double depth, ForceCalculation &fc, double cellSize, double sigma) : Boundary{width, height, depth, fc, cellSize, sigma} {}
