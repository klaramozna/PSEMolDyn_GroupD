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

void Cell::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    for(auto & p1 : particles){
        for(auto & p2 : particles){
            if(p2 != p1){
                function(p1, p2);
            }
        }
    }
}

void Cell::interactWithCell(Cell cell, const std::function<void(Particle &, Particle &)> &function) {
    for(auto & p1 : particles){
        for(auto & p2 : cell){
            function(p1, p2);
        }
    }
}

