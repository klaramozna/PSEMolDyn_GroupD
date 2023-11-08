//
// Created by klara on 26.10.23.
//

#ifndef PSEMOLDYN_GROUPD_VECTORDOUBLE3_H
#define PSEMOLDYN_GROUPD_VECTORDOUBLE3_H


#include <vector>
#include <array>

/**
 * @file Particle.h
 *
 * @brief Provides vector operations using simple operators.
 */

class VectorDouble3 {
private:
    /**
     * @brief Stores values of the vector.
     */
    std::array<double, 3> values;
public:
    VectorDouble3() = default;

    /**
     * @brief Creates a vector of size 3, using the values of the given array.
     * @param array contains the values, given to the created vector.
     */
    explicit VectorDouble3(const std::array<double, 3>& array);

    /**
     * @brief Adds other to this and returns the result.
     * @param other is another vector that has to be of the same size as the object this function is being invoked on.
     * @return The resulting vector of the addition.
     */
    VectorDouble3 operator+=(const VectorDouble3 &other);

    /**
     * @brief Subtracts other from this and returns the result.
     * @param other is another vector that has to be of the same size as the object this function is being invoked on.
     * @return The resulting vector of the subtraction.
     */
    VectorDouble3 operator-=(const VectorDouble3 &other);

    /**
     * @brief Returns the L2 norm (euclidean norm) of the vector.
     * @return L2 norm of the vector.
     */
    double getL2Norm() const;

    /**
     * @brief Prints the vector on stdout.
     */
    void print() const;

    /**
     * @brief Converts the vector to ann array (only available for vectors of size 3).
     * @return resulting array, containing the values of the vector.
     */
    std::array<double, 3> convertToArray() const;

    /**
     * @brief Adds two vectors and returns result.
     * @param vec1 left vector.
     * @param vec2 right vector.
     * @return resulting vector of the addition.
     */
    friend VectorDouble3 operator+(const VectorDouble3 &vec1, const VectorDouble3 &vec2);

    /**
     * @brief Subtracts vec2 from vec1 and returns result.
     * @param vec1 left vector.
     * @param vec2 right vector.
     * @return resulting vector of the subtraction.
     */
    friend VectorDouble3 operator-(const VectorDouble3 &vec1, const VectorDouble3 &vec2);

    /**
     * @brief Multiplies the vector with a scalar.
     * @param scalar is the value the vector is multiplied with.
     * @param vec is the vector that the scalar is multiplied with.
     * @return resulting vector.
     */
    friend VectorDouble3 operator*(double scalar, const VectorDouble3 &vec);
};


#endif //PSEMOLDYN_GROUPD_VECTORDOUBLE3_H
