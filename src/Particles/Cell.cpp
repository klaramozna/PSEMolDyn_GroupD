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

void Cell::addParticle(std::shared_ptr<Particle> p) {
    particles.push_back(p);
}

void Cell::deleteParticle(std::shared_ptr<Particle> p) {
    particles.erase(std::remove(particles.begin(), particles.end(), p), particles.end());
}

bool Cell::contains(const Particle& p) {
    for(const auto& it : particles){
        if(*it == p){
            return true;
        }
    }
    return false;
}

void Cell::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    for(auto outer = particles.begin(); outer != particles.end(); outer++){
        auto inner = outer;
        inner++;
        for(auto in2 = inner; in2 != particles.end(); in2++){
            if(getDistance((*outer)->getXVector(), (*in2)->getXVector()) <= cutoffRadius){
                function(*(*outer), *(*in2));
            }

        }
    }
}

Cell::Cell(const Cell &c) {
    this->cutoffRadius = c.cutoffRadius;
    // Deep copy of the particles vector
    for (const auto& particle : c.particles) {
        particles.push_back(particle); // Assuming Particle has a copy constructor
    }
}

