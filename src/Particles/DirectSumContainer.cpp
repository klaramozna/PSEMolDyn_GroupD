//
// Created by klara on 30.10.23.
//

#include "DirectSumContainer.h"

#include <utility>
#include <stdexcept>

using lui = long unsigned int;

std::vector<Particle>::iterator DirectSumContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator DirectSumContainer::end() {
    return particles.end();
}

DirectSumContainer::DirectSumContainer(std::vector<Particle> particles) {
    this->particles = std::move(particles);
}

void DirectSumContainer::addParticle(const Particle& particle) {
    this->particles.push_back(particle);
}

size_t DirectSumContainer::getSize() {
    return particles.size();
}

DirectSumContainer::PairIterator::PairIterator(std::vector<Particle>::size_type outer, std::vector<Particle>::size_type inner, std::vector<Particle> &vec): p(vec){
    outerIndex = outer;
    innerIndex = inner;
}

std::pair<Particle &, Particle &> DirectSumContainer::PairIterator::operator*() const {
    if(inRange()){
        return std::pair<Particle &, Particle &>{p[outerIndex], p[innerIndex]};
    }
    else{
        throw std::out_of_range("Iterator out of range cannot be dereferenced.");
    }

}

DirectSumContainer::PairIterator &DirectSumContainer::PairIterator::operator++() {
    if(outerIndex >= p.size() && innerIndex >= p.size()){           // both inner and outer loops are at the end
        return *this;
    }
    if(innerIndex < p.size() - 1){                                  // the inner loop has not finished yet
        innerIndex++;
        if(innerIndex == outerIndex) ++(*this);
        return *this;
    }
    if(innerIndex >= p.size() - 1 && outerIndex < p.size() - 2){    // inner loop has finished, but outer loop still has particles left
        outerIndex++;
        innerIndex = outerIndex + 1;
        return *this;
    }
    else{                                                           // both inner and outer loops have gone through all elements
        innerIndex = p.size();
        outerIndex = p.size();
        return *this;
    }
}

bool operator==(const DirectSumContainer::PairIterator &a, const DirectSumContainer::PairIterator &b) {
    return a.innerIndex == b.innerIndex && a.outerIndex == b.outerIndex;
}

bool operator!=(const DirectSumContainer::PairIterator &a, const DirectSumContainer::PairIterator &b) {
    return a.innerIndex != b.innerIndex || a.outerIndex != b.outerIndex;
}

bool DirectSumContainer::PairIterator::inRange() const {
    return innerIndex < p.size() && outerIndex < p.size() && innerIndex >= 0 && outerIndex >= 0;
}

DirectSumContainer::PairIterator DirectSumContainer::beginPair() {
    if(particles.size() < 2){
        throw std::runtime_error("Pair iterator cannot be used, since there are less than two particles in the container.");
    }
    return PairIterator{0, 1, particles};
}

DirectSumContainer::PairIterator DirectSumContainer::endPair() {
    if(particles.size() < 2){
        throw std::runtime_error("Pair iterator cannot be used, since there are less than two particles in the container.");
    }
    return PairIterator{particles.size(), particles.size(), particles};
}

std::vector<Particle> DirectSumContainer::getParticleVector() {
    return particles;
}

void DirectSumContainer::reserveInVector(size_t n) {
    particles.reserve(n);
}

void DirectSumContainer::applyToAll(const std::function<void(Particle &)>& function) {
    for(auto & particle : particles){
        function(particle);
    }
}

void DirectSumContainer::addParticles(const DirectSumContainer &container) {
    particles.insert(particles.end(), container.particles.begin(), container.particles.end());
}

void DirectSumContainer::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    for(lui i = 0; i < particles.size() - 1; i++){
        for(lui j = i + 1; j < particles.size(); j++){
            function(particles[i], particles[j]);
        }
    }
}
