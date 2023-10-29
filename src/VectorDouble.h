//
// Created by klara on 26.10.23.
//

#ifndef PSEMOLDYN_GROUPD_VECTORDOUBLE_H
#define PSEMOLDYN_GROUPD_VECTORDOUBLE_H


#include <vector>
#include <array>

class VectorDouble {
private:
    std::vector<double> values;
public:
    VectorDouble() = default;

    explicit VectorDouble(std::vector<double>::size_type size);

    explicit VectorDouble(const std::vector<double> &vector);

    explicit VectorDouble(const std::array<double, 3>& array);

    VectorDouble operator+=(const VectorDouble &other);

    VectorDouble operator-=(const VectorDouble &other);

    double getL2Norm() const;

    void print() const;

    std::array<double, 3> convertToArray() const;

    friend VectorDouble operator+(const VectorDouble &vec1, const VectorDouble &vec2);

    friend VectorDouble operator-(const VectorDouble &vec1, const VectorDouble &vec2);

    friend VectorDouble operator*(double scalar, const VectorDouble &vec);
};


#endif //PSEMOLDYN_GROUPD_VECTORDOUBLE_H
