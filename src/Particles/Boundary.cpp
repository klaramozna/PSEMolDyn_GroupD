//
// Created by klara on 27.11.23.
//

#include "Boundary.h"

bool Boundary::isOutside(const Particle &p) {
    return !isInside(p);
}
