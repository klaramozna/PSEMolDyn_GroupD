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
    auto allBoundaries = getBoundariesOfParticle(particle);

    for (const auto & category : {BoundaryType::REFLECTIVE, BoundaryType::PERIODIC, BoundaryType::OUTFLOW}) {
        std::vector<BoundaryDirection> intersectingBoundaries;

        for (const auto &boundary : allBoundaries) {
            int boundaryIndex = static_cast<int>(boundary);

            if (boundaryTypes[boundaryIndex] == category) {
                intersectingBoundaries.push_back(boundary);
            }
        }

        if (!intersectingBoundaries.empty()) {
            switch (category) {
                case BoundaryType::REFLECTIVE:
                    applyReflectiveForce(particle, intersectingBoundaries);
                    break;
                case BoundaryType::PERIODIC:
                    applyPeriodicBoundary(particle);
                    particle.markForMirroring();
                    break;
                case BoundaryType::OUTFLOW:
                    break;
            }
        }
    }
}

void BoundaryEnforcer::applyReflectiveForce(Particle &p, std::vector<BoundaryDirection> directions) {
    std::array<double, 3> particlePosition = p.getX();
    std::array<double, 3> opposingParticlePosition = particlePosition;

    for (auto direction : directions) {
        switch (direction) {
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

    if (particlePosition[0] < container.getCellSize()[0] && particlePosition[0] > 0) {
        result.push_back(BoundaryDirection::LEFT);
    } else if (dimensions[0] - particlePosition[0] < container.getCellSize()[0] && dimensions[0] - particlePosition[0] > 0) {
        result.push_back(BoundaryDirection::RIGHT);
    }

    if (particlePosition[1] < container.getCellSize()[1] && particlePosition[1] > 0) {
        result.push_back(BoundaryDirection::BOTTOM);
    } else if (dimensions[1] - particlePosition[1] < container.getCellSize()[1] && dimensions[1] - particlePosition[1] > 0) {
        result.push_back(BoundaryDirection::TOP);
    }

    if (particlePosition[2] < container.getCellSize()[2] && particlePosition[2] > 0) {
        result.push_back(BoundaryDirection::FRONT);
    } else if (dimensions[2] - particlePosition[2] < container.getCellSize()[2] && dimensions[2] - particlePosition[2] > 0) {
        result.push_back(BoundaryDirection::BACK);
    }

    return result;
}

void BoundaryEnforcer::applyPeriodicBoundary(Particle &particle) {
    std::array<double, 3> particlePosition = particle.getX();
    std::array<double, 3> cellSize = container.getCellSize();

    // Determine the loop limits based on the enabled periodic dimensions
    int dxMin = (boundaryTypes[5] == BoundaryType::PERIODIC ? -1 : 0);
    int dxMax = (boundaryTypes[3] == BoundaryType::PERIODIC ? 1 : 0);
    int dyMin = (boundaryTypes[4] == BoundaryType::PERIODIC ? -1 : 0);
    int dyMax = (boundaryTypes[2] == BoundaryType::PERIODIC ? 1 : 0);
    int dzMin = (boundaryTypes[0] == BoundaryType::PERIODIC ? -1 : 0);
    int dzMax = (boundaryTypes[1] == BoundaryType::PERIODIC ? 1 : 0);

    // Replicate the particle in all 26 directions
    for (int dx = dxMin; dx <= dxMax; ++dx) {
        for (int dy = dyMin; dy <= dyMax; ++dy) {
            for (int dz = dzMin; dz <= dzMax; ++dz) {
                if (dx == 0 && dy == 0 && dz == 0) {
                    // Skip the original direction
                    continue;
                }

                // Calculate the mirrored position
                double mirroredX = particlePosition[0] + dx * dimensions[0];
                double mirroredY = particlePosition[1] + dy * dimensions[1];
                double mirroredZ = particlePosition[2] + dz * dimensions[2];

                if (isHaloParticle(mirroredX, mirroredY, mirroredZ)) {
                    Particle replicatedParticle(particle);
                    replicatedParticle.unmarkForMirroring();
                    replicatedParticle.setX(mirroredX, mirroredY, mirroredZ);
                    replicatedParticle.setV(0,0,0);
                    container.addParticle(replicatedParticle);
                }
            }
        }
    }
}

bool BoundaryEnforcer::isHaloParticle(double x, double y, double z) {
    return (x > -container.getCellSize()[0] && x < 0) ||
           (x > dimensions[0] && x < dimensions[0] + container.getCellSize()[0]) ||
           (y > -container.getCellSize()[1] && y < 0) ||
           (y> dimensions[1] && y < dimensions[1] + container.getCellSize()[1]) ||
           (z > -container.getCellSize()[2] && z < 0) ||
           (z > dimensions[2] && z < dimensions[2] + container.getCellSize()[2]);
}


