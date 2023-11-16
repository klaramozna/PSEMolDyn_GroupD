/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <iostream>
#include "utils/ArrayUtils.h"

Particle::Particle(int type_arg) {
    type = type_arg;
    f = {0., 0., 0.};
    old_f = {0., 0., 0.};
}

Particle::Particle(const Particle &other) {
    x = other.x;
    v = other.v;
    f = other.f;
    old_f = other.old_f;
    m = other.m;
    type = other.type;
}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, int type_arg) : f{0., 0., 0.}, old_f{0., 0., 0.} {
    x = x_arg;
    v = v_arg;
    m = m_arg;
    type = type_arg;
}

Particle::~Particle() {}

const std::array<double, 3> &Particle::getX() const { return x; }

const std::array<double, 3> &Particle::getV() const { return v; }

const std::array<double, 3> &Particle::getF() const { return f; }

const std::array<double, 3> &Particle::getOldF() const { return old_f; }

double Particle::getM() const { return m; }

int Particle::getType() const { return type; }

std::string Particle::toString() const {
    std::stringstream stream;
    stream << "Particle: X:" << x << " v: " << v << " f: " << f
           << " old_f: " << old_f << " type: " << type;
    return stream.str();
}

bool Particle::operator==(const Particle &other) const {
    return (x == other.x) and (v == other.v) and (f == other.f) and (m == other.m) and (old_f == other.old_f);
}

bool Particle::operator!=(const Particle& other) const {
    return (!(this == &other));
}

VectorDouble3 Particle::getXVector() const {
    return VectorDouble3(x);
}

VectorDouble3 Particle::getVVector() const {
    return VectorDouble3(v);
}

VectorDouble3 Particle::getFVector() const {
    return VectorDouble3(f);
}

VectorDouble3 Particle::getOldFVector() const {
    return VectorDouble3(old_f);
}

void Particle::setX(const VectorDouble3 &position) {
    x = position.convertToArray();
}

void Particle::setV(const VectorDouble3 &velocity) {
     v = velocity.convertToArray();
}

void Particle::setF(const VectorDouble3 &force) {
    f = force.convertToArray();
}

void Particle::setOldF(const VectorDouble3 &oldForce) {
    old_f = oldForce.convertToArray();
}

void Particle::setX(double x, double y, double z) {
    (this->x)[0] = x;
    (this->x)[1] = y;
    (this->x)[2] = z;
}

void Particle::setV(double x, double y, double z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void Particle::setF(double x, double y, double z) {
    f[0] = x;
    f[1] = y;
    f[2] = z;
}

void Particle::setOldF(double x, double y, double z) {
    old_f[0] = x;
    old_f[1] = y;
    old_f[2] = z;
}

std::ostream &operator<<(std::ostream &stream, Particle &p) {
    stream << p.toString();
    return stream;
}
