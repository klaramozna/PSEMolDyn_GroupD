/*
 * Particle.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "Particle.h"

#include <iostream>
#include "../utils/ArrayUtils.h"

Particle::Particle(int type_arg) {
    type = type_arg;
    f = VectorDouble3(std::array<double, 3>{0, 0, 0});
    old_f = VectorDouble3(std::array<double, 3>{0, 0, 0});
    markedForMirroring = false;
    markedForDeleting = false;
}

Particle::Particle(const Particle &other) {
    x = other.x;
    v = other.v;
    f = other.f;
    old_f = other.old_f;
    m = other.m;
    type = other.type;
    epsilon = other.epsilon;
    sigma = other.sigma;
    markedForMirroring = other.markedForMirroring;
    markedForDeleting = other.markedForDeleting;
    stiffness = other.stiffness;
    bond_length= other.bond_length;
    parallel_Neighbours = other.parallel_Neighbours;
    diagonal_Neighbours = other.diagonal_Neighbours;
    id = other.id;
}

Particle::Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg,
                   double m_arg, int type_arg) : f{VectorDouble3(std::array<double, 3>{0, 0, 0})}, old_f{VectorDouble3(std::array<double, 3>{0, 0, 0})} {
    x = VectorDouble3(x_arg);
    v = VectorDouble3(v_arg);
    m = m_arg;
    type = type_arg;
    epsilon = 1.0;
    sigma = 1.0;
    markedForMirroring = false;
    markedForDeleting = false;
}

Particle::~Particle() {}

const std::array<double, 3> Particle::getX() const { return x.convertToArray(); }

const std::array<double, 3> Particle::getV() const { return v.convertToArray(); }

const std::array<double, 3> Particle::getF() const { return f.convertToArray(); }

const std::array<double, 3> Particle::getOldF() const { return old_f.convertToArray(); }

double Particle::getM() const { return m; }

int Particle::getType() const { return type; }

std::string Particle::toString() const {
    std::stringstream stream;
    stream << "Particle: X:" << x.convertToArray() << " v: " << v.convertToArray() << " f: " << f.convertToArray()
           << " old_f: " << old_f.convertToArray() << " type: " << type;
    return stream.str();
}

bool Particle::operator==(const Particle &other) const {
    return (x == other.x) and (v == other.v) and (f == other.f) and (m == other.m) and (old_f == other.old_f);
}

bool Particle::operator!=(const Particle& other) const {
    return (!(this == &other));
}

VectorDouble3 Particle::getXVector() const {
    return x;
}

VectorDouble3 Particle::getVVector() const {
    return v;
}

VectorDouble3 Particle::getFVector() const {
    return f;
}

VectorDouble3 Particle::getOldFVector() const {
    return old_f;
}

double Particle::getStiffness() const {
    return stiffness;
}

double Particle::getBondLength() const {
    return bond_length;
}


std::vector<std::shared_ptr<Particle>> Particle::getParallelNeighbours() const {
    return parallel_Neighbours;
}


std::vector<std::shared_ptr<Particle>> Particle::getDiagonalNeighbours() const{
    return diagonal_Neighbours;
}

int Particle::getId() const{
    return id;
}

void Particle::setX(const VectorDouble3 &position) {
    x = position;
}

void Particle::setV(const VectorDouble3 &velocity) {
     v = velocity;
}

void Particle::setF(const VectorDouble3 &force) {
    f = force;
}

void Particle::setOldF(const VectorDouble3 &oldForce) {
    old_f = oldForce;
}

void Particle::setX(double x, double y, double z) {
    this->x = VectorDouble3(std::array<double, 3>{x, y, z});
}

void Particle::setV(double x, double y, double z) {
    this->v = VectorDouble3(std::array<double, 3>{x, y, z});
}

void Particle::setF(double x, double y, double z) {
    this->f = VectorDouble3(std::array<double, 3>{x, y, z});
}

void Particle::setOldF(double x, double y, double z) {
    this->old_f = VectorDouble3(std::array<double, 3>{x, y, z});
}

void Particle::setParallelNeighbours(std::vector<std::shared_ptr<Particle>> pointers_parallel){
    parallel_Neighbours = pointers_parallel;
}

void Particle::setDiagonalNeighbours(std::vector<std::shared_ptr<Particle>> pointers_diagonal){
    diagonal_Neighbours = pointers_diagonal;
}
void Particle::setStiffness(double val) {
    stiffness = val;
}

void Particle::setBondLength(double val){
    bond_length = val;
}

void Particle::setId(int val) {
    id = val;
}

void Particle::markForMirroring() {
    markedForMirroring = true;
}

bool Particle::isMarkedForMirroring() const {
    return markedForMirroring;
}

void Particle::unmarkForMirroring() {
    markedForMirroring = false;
}

void Particle::markForDeleting() {
    markedForDeleting = true;
}

bool Particle::isMarkedForDeleting() const {
    return markedForDeleting;
}


std::ostream &operator<<(std::ostream &stream, Particle &p) {
    stream << p.toString();
    return stream;
}
