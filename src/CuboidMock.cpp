//
// Created by rodff on 14.11.23.
//

#include "CuboidMock.h"

CuboidMock::CuboidMock(std::array<double,3> llc,
                       std::array<int,3> numParticles,
                       std::array<double,3> distances,
                       std::array<double,3> initialVelocity,
                       double m) : llc{llc},
                                   numParticles(numParticles),
                                   distances{distances},
                                   m{m},
                                   initialVelocity{initialVelocity}
                                   {}

CuboidMock::~CuboidMock() = default;

bool operator==(const CuboidMock &c1, const CuboidMock &c2) {
    return (c1.initialVelocity == c2.initialVelocity) &&
           (c1.numParticles == c2.numParticles) &&
           (c1.distances == c2.distances) &&
           (c1.llc == c2.llc) &&
           (c1.m == c2.m);
}

