//
// Created by klara on 22.11.23.
//

#include "Cell.h"

Cell::iterator_type Cell::begin(){
    return particles.begin();
}

Cell::iterator_type Cell::end(){
    return particles.end();
}

void Cell::addParticle(const Particle& p) {
    particles.insert(particles.end(), p);
}

void Cell::deleteParticle(const Particle &p) {
    particles.remove(p);
}

bool Cell::contains(Particle p) {
    return std::find(particles.begin(), particles.end(), p) != particles.end();
}

void Cell::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    for(auto outer = particles.begin(); outer != particles.end(); outer++){
        auto inner = outer;
             inner++;
              for(auto in2 = inner; in2 != particles.end(); in2++){
                  if(getDistance(outer->getXVector(), in2->getXVector()) <= cutoffRadius){
                      function(*outer, *in2);
                  }
              }
    }
}

