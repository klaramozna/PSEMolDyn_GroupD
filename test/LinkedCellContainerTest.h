//
// Created by klara on 30.11.23.
//

#ifndef PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
#define PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H

#include "../src/Particles/LinkedCellContainer.h"
#include "../src/Particles/Boundary.h"
#include <gtest/gtest.h>

// Define a mock ForceCalculation class for testing
class MockForceCalculation : public ForceCalculation {
public:
    // Override CalculateForces to return a known force vector for testing
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override {
        // You can customize this for your specific testing needs
        return p1.getXVector() - p2.getXVector();
    }
};

class LinkedCellContainerTest : public testing::Test{
protected:
    LinkedCellContainer container{Boundary(8, 8, 2, 1.0, {"Reflective", "Reflective","Reflective","Reflective","Reflective","Reflective"}), 2};
    Particle p1{std::array<double, 3>{2, 0, 0.5}, std::array<double, 3>{}, 0};
    Particle p2{std::array<double, 3>{6.5, -1.5, 0.5}, std::array<double, 3>{}, 0};
    Particle p3{std::array<double, 3>{5.25, 4.1, 0.5}, std::array<double, 3>{}, 0};
    Particle p4{std::array<double, 3>{0.5, 6.1, 0.5}, std::array<double, 3>{}, 0};

    Particle p1Shifted{std::array<double, 3>{2, 0-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p2Shifted{std::array<double, 3>{6.5, -1.5-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p3Shifted{std::array<double, 3>{5.25, 4.1-2, 0.5}, std::array<double, 3>{}, 0};
    Particle p4Shifted{std::array<double, 3>{0.5, 6.1-2, 0.5}, std::array<double, 3>{}, 0};
    void SetUp() override;
    LinkedCellContainer boundaryContainer{Boundary(3, 3, 3, 1.0, {"Reflective", "Reflective","Reflective","Reflective","Reflective","Reflective"}), 1};
    Particle boundary1{std::array<double, 3>{1.5, 1.5, 1.5}, std::array<double, 3>{}, 0};
    Particle boundary2{std::array<double, 3>{0.5, 1.5, 1.5}, std::array<double, 3>{}, 0};
    Particle boundaryChanged2{std::array<double, 3>{0.5, 1.5, 1.5}, std::array<double, 3>{50, 50, 50}, 0};

    LinkedCellContainer wrongAlignmentContainer{Boundary(6, 5, 4.5, 1.0, {"Reflective", "Reflective","Reflective","Reflective","Reflective","Reflective"}), 1};
    Particle p1WrongAlignment{std::array<double, 3>{0.5, -0.00000001, 2.25}, std::array<double, 3>{}, 0};
    Particle p2WrongAlignment{std::array<double, 3>{1.7, 0.1, 2.25}, std::array<double, 3>{}, 0};
    Particle p3WrongAlignment{std::array<double, 3>{1.4, 3.2, 2.25}, std::array<double, 3>{}, 0};

    Particle p2BoundaryWrongAlignment{std::array<double, 3>{1.7, 0.1, 2.25}, std::array<double, 3>{50, 50, 50}, 0};
    Particle p3BoundaryWrongAlignment{std::array<double, 3>{1.4, 3.2, 2.25}, std::array<double, 3>{50, 50, 50}, 0};
};


#endif //PSEMOLDYN_GROUPD_LINKEDCELLCONTAINERTEST_H
