//
// Created by klara on 22.11.23.
//

#include "Cell.h"

Cell::Cell(const std::vector<Particle> &p, Cell::Type t) {
    type = t;
    particles = p;
}

Cell::iterator_type Cell::begin() {
    return particles.begin();
}

Cell::iterator_type Cell::end() {
    return particles.end();
}

Cell::Type Cell::getType() {
    return type;
}

void Cell::setType(Cell::Type t) {
    type = t;
}
