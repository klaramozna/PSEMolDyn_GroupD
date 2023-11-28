//
// Created by klara on 22.11.23.
//

#include "Cell.h"

Cell::Cell(const std::list<Particle> &p, Cell::Type t) {
    particles = p;
}

Cell::iterator_type Cell::begin() {
    return particles.begin();
}

Cell::iterator_type Cell::end() {
    return particles.end();
}

void Cell::addParticle(const Particle& p) {
    particles.insert(particles.end(), p);
}

void Cell::deleteParticle(const Particle &p) {
    particles.remove(p);
}
