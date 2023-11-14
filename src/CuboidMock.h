//
// Created by rodff on 14.11.23.
//

#ifndef PSEMOLDYN_GROUPD_CUBOIDMOCK_H
#define PSEMOLDYN_GROUPD_CUBOIDMOCK_H

#include <array>
#include "VectorDouble3.h"

class CuboidMock {
private:
    std::array<double,3> llc;
    std::array<int,3> numParticles;
    std::array<double,3> distances;
    double m;

    std::array<double,3> initialVelocity;
public:
    CuboidMock(std::array<double,3> llc,
               std::array<int,3> numParticles,
               std::array<double,3> distances,
               std::array<double,3> initialVelocity,
               double m);

    ~CuboidMock();
    friend bool operator==(const CuboidMock &c1, const CuboidMock &c2);
};


#endif //PSEMOLDYN_GROUPD_CUBOIDMOCK_H
#