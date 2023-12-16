//
// Created by rodff on 14.12.23.
//

#include "BoundaryEnforcer.h"

BoundaryEnforcer::BoundaryEnforcer(double sigma, LinkedCellContainer &container, std::array<double, 3> dimensions,
                                   std::array<BoundaryType, 6> boundaryTypes, ForceCalculation &fc) : container(container),
                                                                                dimensions(dimensions),
                                                                                boundaryTypes(boundaryTypes),
                                                                                sigma{sigma},
                                                                                fc{fc} {}


void BoundaryEnforcer::applyBoundaryConditionsForParticle(Particle &particle) {
    auto boundariesOfParticle = getBoundariesOfParticle(particle);

    for (auto boundaryOfParticle : boundariesOfParticle) {
        switch (boundaryTypes[static_cast<int>(boundaryOfParticle)]) {
            case BoundaryType::REFLECTIVE:
                applyReflectiveForce(particle, boundaryOfParticle);
                break;
            case BoundaryType::PERIODIC:
                // TODO: Implement Periodic Boundary
                break;
            case BoundaryType::OUTFLOW:
                particle.markForDeletion();
                break;
        }
    }
}

void BoundaryEnforcer::applyReflectiveForce(Particle &p, BoundaryDirection boundaryofParticle) {
    std::array<double, 3> particlePosition = p.getX();
    std::array<double, 3> opposingParticlePosition = particlePosition;

    switch (boundaryofParticle) {
        case BoundaryDirection::LEFT:
            opposingParticlePosition[0] -= 2 * particlePosition[0];
            break;
        case BoundaryDirection::RIGHT:
            opposingParticlePosition[0] += 2 * std::abs(particlePosition[0] - dimensions[0]);
            break;
        case BoundaryDirection::BOTTOM:
            opposingParticlePosition[1] -= 2 * particlePosition[1];
            break;
        case BoundaryDirection::TOP:
            opposingParticlePosition[1] += 2 * std::abs(particlePosition[1] - dimensions[1]);
            break;
        case BoundaryDirection::FRONT:
            opposingParticlePosition[2] -= 2 * particlePosition[2];
            break;
        case BoundaryDirection::BACK:
            opposingParticlePosition[2] += 2 * std::abs(particlePosition[2] - dimensions[2]);
            break;
    }

    if (getDistance(VectorDouble3(particlePosition), VectorDouble3(opposingParticlePosition)) <= SIXTH_ROOT_OF_TWO * sigma) {
        auto opposingParticle = Particle(opposingParticlePosition, {0.0, 0.0, 0.0}, p.getM());
        auto result = fc.CalculateForces(p, opposingParticle);
        p.setF(p.getFVector() + result);
    }
}

std::vector<BoundaryDirection> BoundaryEnforcer::getBoundariesOfParticle(Particle &particle) {
    std::vector<BoundaryDirection> result;

    std::array<double, 3> particlePosition = particle.getX();

    if (particlePosition[0] < container.getCellSizeX() && particlePosition[0] > 0) {
        result.push_back(BoundaryDirection::LEFT);
    } else if (dimensions[0] - particlePosition[0] < container.getCellSizeX() && dimensions[0] - particlePosition[0] > 0) {
        result.push_back(BoundaryDirection::RIGHT);
    }

    if (particlePosition[1] < container.getCellSizeY() && particlePosition[1] > 0) {
        result.push_back(BoundaryDirection::BOTTOM);
    } else if (dimensions[1] - particlePosition[1] < container.getCellSizeY() && dimensions[1] - particlePosition[1] > 0) {
        result.push_back(BoundaryDirection::TOP);
    }

    if (particlePosition[2] < container.getCellSizeZ() && particlePosition[2] > 0) {
        result.push_back(BoundaryDirection::FRONT);
    } else if (dimensions[2] - particlePosition[2] < container.getCellSizeZ() && dimensions[2] - particlePosition[2] > 0) {
        result.push_back(BoundaryDirection::BACK);
    }

    return result;
}


