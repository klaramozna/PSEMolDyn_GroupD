#pragma once

#include "ForceCalculation.h"
#include "MixingRuleLennardJones.h"

class SmoothedLennardJones : public ForceCalculation {
private:
    double r_c;
    double r_l;
    MixingRuleLennardJones mixingRuleLennardJones; 

public:
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2) override;

    /**
    * @brief constructor to initialize eps and sigma
    * @param r_c cutoff radius
    * @param r_l 
    **/
    SmoothedLennardJones(double r_c_val, double r_l_val) : r_c(r_c_val), r_l(r_l_val) {}

    ~SmoothedLennardJones() override = default; // Virtual destructor for polymorphism.
};