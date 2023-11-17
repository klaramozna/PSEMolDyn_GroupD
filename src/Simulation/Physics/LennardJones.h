#pragma once

#include "ForceCalculation.h"

class LennardJones : public ForceCalculation {
private:
    double eps;
    double sigma;
public:
    VectorDouble3 CalculateForces(const Particle& p1, const Particle& p2);
   
    /**
    * @brief constructor to initialize eps and sigma
    * @param epsilon
    * @param sigma_val
    **/
    LennardJones(double epsilon, double sigma_val) : eps(epsilon), sigma(sigma_val) {}

    /**
    * @brief setter for epsilon
    * @param newEps
    **/
    void setEpsilon(double newEps) {
        eps = newEps;
    }
    /**
    * @brief setter for sigma
    * @param newSigma
    **/
    void setSigma(double newSigma) {
        sigma = newSigma;
    }

    /**
    * @brief getter for eps
    * @return epsilon
    **/
    double getEpsilon() const {
        return eps;
    }
    /**
    * @brief getter for sigma
    * @return sigma
    **/
    double getSigma() const {
        return sigma;
    }

    ~LennardJones() override = default; // Virtual destructor for polymorphism.
};