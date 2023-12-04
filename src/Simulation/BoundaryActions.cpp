//
// Created by rodff on 04.12.23.
//

#include "BoundaryActions.h"

std::unique_ptr<Particle> BoundaryActions::createOpposingParticle(const Particle &p, CuboidBoundary &boundary, double sigma) {
    std::array<double, 3> particlePosition = p.getX();
    std::array<double, 3> boundaryDimensions = boundary.getDimensions();

    auto opposingParticle = std::make_unique<Particle>(Particle(findOpposingParticle(p, boundary), {0.0, 0.0, 0.0}, p.getM()));

    return opposingParticle;
}

std::array<double,3> BoundaryActions::findOpposingParticle(const Particle& p, CuboidBoundary& boundary) {
    std::array<double, 3> particlePosition = p.getX();
    std::array<double, 3> boundaryDimensions = boundary.getDimensions();

    std::array<double, 3> opposingParticlePosition = particlePosition;

    // Check x-axis
    if (particlePosition[0] < boundaryDimensions[0] / 2.0) {
        opposingParticlePosition[0] += boundaryDimensions[0];
    } else if (particlePosition[0] > boundaryDimensions[0] / 2.0) {
        opposingParticlePosition[0] -= boundaryDimensions[0];
    }

    // Check y-axis
    if (particlePosition[1] < boundaryDimensions[1] / 2.0) {
        opposingParticlePosition[1] += boundaryDimensions[1];
    } else if (particlePosition[1] > boundaryDimensions[1] / 2.0) {
        opposingParticlePosition[1] -= boundaryDimensions[1];
    }

    // Check z-axis
    if (particlePosition[2] < boundaryDimensions[2] / 2.0) {
        opposingParticlePosition[2] += boundaryDimensions[2];
    } else if (particlePosition[2] > boundaryDimensions[2] / 2.0) {
        opposingParticlePosition[2] -= boundaryDimensions[2];
    }

    return opposingParticlePosition;
}
