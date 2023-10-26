//
// Created by klara on 26.10.23.
//

#include "VectorDouble.h"
#include <stdexcept>
#include <cmath>
#include <iostream>


VectorDouble::VectorDouble(std::vector<double>::size_type size) {
    values.resize(size, 0.);
}

VectorDouble::VectorDouble(const std::vector<double> &vector) {
    values = vector;
}

VectorDouble VectorDouble::operator+=(const VectorDouble &other) {
    if (other.values.size() != values.size()) {
        throw std::invalid_argument("Vectors of different sizes cannot be added.");
    }
    for (int i = 0; i < values.size(); i++) {
        values[i] += other.values[i];
    }
    return *this;
}

VectorDouble VectorDouble::operator-=(const VectorDouble &other) {
    if (other.values.size() != values.size()) {
        throw std::invalid_argument("Vectors of different sizes cannot be subtracted.");
    }
    for (int i = 0; i < values.size(); i++) {
        values[i] -= other.values[i];
    }
    return *this;
}

double VectorDouble::getL2Norm() const {
    double norm(0.);
    for (auto value: values) {
        norm += value * value;
    }
    return sqrt(norm);
}

void VectorDouble::print() const {
    for (auto value: values) {
        std::cout << "|" << value << "|" << std::endl;
    }
}

VectorDouble operator+(const VectorDouble &vec1, const VectorDouble &vec2) {
    if (vec1.values.size() != vec2.values.size()) {
        throw std::invalid_argument("Vectors of different sizes cannot be added.");
    }
    VectorDouble result(vec1.values.size());
    for (int i = 0; i < result.values.size(); i++) {
        result.values[i] = vec1.values[i] + vec2.values[i];
    }
    return result;
}

VectorDouble operator-(const VectorDouble &vec1, const VectorDouble &vec2) {
    if (vec1.values.size() != vec2.values.size()) {
        throw std::invalid_argument("Vectors of different sizes cannot be subtracted.");
    }
    VectorDouble result(vec1.values.size());
    for (int i = 0; i < result.values.size(); i++) {
        result.values[i] = vec1.values[i] - vec2.values[i];
    }
    return result;
}

VectorDouble operator*(double scalar, const VectorDouble &vec) {
    VectorDouble result(vec.values.size());
    for (int i = 0; i < result.values.size(); i++) {
        result.values[i] = scalar * vec.values[i];
    }
    return result;
}
