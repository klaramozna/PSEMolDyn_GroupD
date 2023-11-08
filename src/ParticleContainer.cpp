//
// Created by klara on 30.10.23.
//

#include "ParticleContainer.h"

#include <utility>
#include <stdexcept>

std::vector<Particle>::iterator ParticleContainer::begin() {
    return particles.begin();
}

std::vector<Particle>::iterator ParticleContainer::end() {
    return particles.end();
}

ParticleContainer::ParticleContainer(std::vector<Particle> particles) {
    this->particles = std::move(particles);
}

void ParticleContainer::addParticle(const Particle& particle) {
    this->particles.push_back(particle);
}

size_t ParticleContainer::getSize() {
    return particles.size();
}

void ParticleContainer::addParticles(std::vector<Particle> toAdd) {
    particles.insert(particles.end(), toAdd.begin(), toAdd.end());
}

ParticleContainer::PairIterator::PairIterator(std::vector<Particle>::size_type outer, std::vector<Particle>::size_type inner, std::vector<Particle> &vec): p(vec){
    outerIndex = outer;
    innerIndex = inner;
}

std::pair<Particle &, Particle &> ParticleContainer::PairIterator::operator*() const {
    if(inRange()){
        return std::pair<Particle &, Particle &>{p[outerIndex], p[innerIndex]};
    }
    else{
        throw std::out_of_range("Iterator out of range cannot be dereferenced.");
    }

}

ParticleContainer::PairIterator &ParticleContainer::PairIterator::operator++() {
    if(outerIndex >= p.size() && innerIndex >= p.size()){           // both inner and outer loops are at the end
        return *this;
    }
    if(innerIndex < p.size() - 1){                                  // the inner loop has not finished yet
        innerIndex++;
        if(innerIndex == outerIndex) ++(*this);
        return *this;
    }
    if(innerIndex >= p.size() - 1 && outerIndex < p.size() - 1){    // inner loop has finished, but outer loop still has particles left
        innerIndex = 0;
        outerIndex++;
        if(innerIndex == outerIndex) ++(*this);
        return *this;
    }
    else{                                                           // both inner and outer loops have gone through all elements
        innerIndex = p.size();
        outerIndex = p.size();
        return *this;
    }
}

bool operator==(const ParticleContainer::PairIterator &a, const ParticleContainer::PairIterator &b) {
    return a.innerIndex == b.innerIndex && a.outerIndex == b.outerIndex;
}

bool operator!=(const ParticleContainer::PairIterator &a, const ParticleContainer::PairIterator &b) {
    return a.innerIndex != b.innerIndex || a.outerIndex != b.outerIndex;
}

bool ParticleContainer::PairIterator::inRange() const {
    return innerIndex < p.size() && outerIndex < p.size() && innerIndex >= 0 && outerIndex >= 0;
}

ParticleContainer::PairIterator ParticleContainer::beginPair() {
    return PairIterator{0, 1, particles};
}

ParticleContainer::PairIterator ParticleContainer::endPair() {
    return PairIterator{particles.size(), particles.size(), particles};
}

std::vector<Particle> &ParticleContainer::getParticleVector() {
    return particles;
}

void ParticleContainer::reserveInVector(size_t n) {
    particles.reserve(n);
}
