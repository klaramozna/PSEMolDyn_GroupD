//
// Created by klara on 26.10.23.
//

#include "VectorDouble3.h"
#include <cmath>
#include <iostream>

using lui = long unsigned int;

double sqrtNewton(double x, double epsilon = 1e-9) {
        double guess = x / 2.0; // Initial guess
        while (std::fabs(guess * guess - x) > epsilon) {
            guess = (guess + x / guess) / 2.0; // Newton's method iteration
        }
        return guess; 
}
VectorDouble3 VectorDouble3::operator+=(const VectorDouble3 &other) {
    for (lui i = 0; i < values.size(); i++) {
        values[i] += other.values[i];
    }
    return *this;
}

VectorDouble3 VectorDouble3::operator-=(const VectorDouble3 &other) {
    for (lui i = 0; i < values.size(); i++) {
        values[i] -= other.values[i];
    }
    return *this;
}

double VectorDouble3::getL2Norm() const {
    double norm(0.);
    for (auto value: values) {
        norm += value * value;
    }
    return sqrtNewton(norm);
}

void VectorDouble3::print() const {
    for (auto value: values) {
        std::cout << "|" << value << "|" << std::endl;
    }
}

VectorDouble3 operator+(const VectorDouble3 &vec1, const VectorDouble3 &vec2) {
    VectorDouble3 result{};
    for (lui i = 0; i < result.values.size(); i++) {
        result.values[i] = vec1.values[i] + vec2.values[i];
    }
    return result;
}

VectorDouble3 operator-(const VectorDouble3 &vec1, const VectorDouble3 &vec2) {
    VectorDouble3 result{};
    for (lui i = 0; i < result.values.size(); i++) {
        result.values[i] = vec1.values[i] - vec2.values[i];
    }
    return result;
}

VectorDouble3 operator*(double scalar, const VectorDouble3 &vec) {
    VectorDouble3 result{};
    for (lui i = 0; i < result.values.size(); i++) {
        result.values[i] = scalar * vec.values[i];
    }
    return result;
}

VectorDouble3::VectorDouble3(const std::array<double, 3> &array): values{} {
    values[0] = array[0];
    values[1] = array[1];
    values[2] = array[2];
}

std::array<double, 3> VectorDouble3::convertToArray() const {
    return values;
}

double VectorDouble3::at(int index) {
    return values.at(index);
}

bool VectorDouble3::operator==(const VectorDouble3& other) const {
    return values == other.values; 
}

double getDistance(const VectorDouble3& v1, const VectorDouble3& v2){
    VectorDouble3 result = v1 - v2;
    return result.getL2Norm();
}

double getDotProduct(const VectorDouble3& v1, const VectorDouble3& v2){
    double sum = 0;
    for(int i = 0; i < 3; i++){
        sum += v1.values[i] * v2.values[i];
    }
    return sum;
}