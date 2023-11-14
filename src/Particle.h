/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>
#include "VectorDouble3.h"

class Particle {

private:
    /**
     * Position of the particle
     */
    std::array<double, 3> x;

    /**
     * Velocity of the particle
     */
    std::array<double, 3> v;

    /**
     * Force effective on this particle
     */
    std::array<double, 3> f;

    /**
     * Force which was effective on this particle
     */
    std::array<double, 3> old_f;

    /**
     * Mass of this particle
     */
    double m;

    /**
     * Type of the particle. Use it for whatever you want (e.g. to separate
     * molecules belonging to different bodies, matters, and so on)
     */
    int type;

public:
    explicit Particle(int type = 0);

    Particle(const Particle &other);

    Particle(
            // for visualization, we need always 3 coordinates
            // -> in case of 2d, we use only the first and the second
            std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg,
            int type = 0);

    virtual ~Particle();

    const std::array<double, 3> &getX() const;

    const std::array<double, 3> &getV() const;

    const std::array<double, 3> &getF() const;

    const std::array<double, 3> &getOldF() const;

    /**
     * @brief Returns the position as a DoubleVector.
     * @return Vector with the values of the position
     */
    VectorDouble3 getXVector() const;

    /**
     * @brief Returns the velocity as a DoubleVector.
     * @return Vector with the values of the velocity
     */
    VectorDouble3 getVVector() const;

    /**
     * @brief Returns the force as a DoubleVector.
     * @return Vector with the values of the force
     */
    VectorDouble3 getFVector() const;

    /**
     * @brief Returns the position in the previous iteration as a DoubleVector.
     * @return Vector with the values of the force.
     */
    VectorDouble3 getOldFVector() const;

    double getM() const;

    int getType() const;

    /**
     * @brief Sets the values of the position based on the given vector.
     * @param position contains the values that will be assigned to the position, needs to be of size 3.
     */
    void setX(const VectorDouble3 &position);

    /**
     * @brief Sets the values of the velocity based on the given vector.
     * @param position contains the values that will be assigned to the velocity, needs to be of size 3.
     */
    void setV(const VectorDouble3 &velocity);

    /**
     * @brief Sets the values of the force based on the given vector.
     * @param position contains the values that will be assigned to the force, needs to be of size 3.
     */
    void setF(const VectorDouble3 &force);

    /**
     * @brief Sets the values of the force in the previous iteration based on the given vector.
     * @param position contains the values that will be assigned to the force, needs to be of size 3.
     */
    void setOldF(const VectorDouble3 &oldForce);

    bool operator==(const Particle &other) const;

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &stream, Particle &p);
