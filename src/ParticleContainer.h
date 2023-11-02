//
// Created by klara on 30.10.23.
//

#ifndef PSEMOLDYN_PARTICLECONTAINER_H
#define PSEMOLDYN_PARTICLECONTAINER_H

#include <vector>
#include "Particle.h"


class ParticleContainer {
private:
    std::vector<Particle> particles;
public:
    class PairIterator;
    using iterator_type = std::vector<Particle>::iterator;
    explicit ParticleContainer(std::vector<Particle> particles);
    ParticleContainer() = default;
    iterator_type begin();
    iterator_type end();
    void addParticle(Particle particle);
    void addParticles(std::vector<Particle> toAdd);
    PairIterator beginPair();
    PairIterator endPair();

    class PairIterator {
    private:
        std::vector<Particle>::size_type outerIndex;
        std::vector<Particle>::size_type innerIndex;
        using value_type = std::pair<Particle&, Particle&>;
        using reference = std::pair<Particle&, Particle&>&;
        std::vector<Particle>& p;
        bool inRange() const;
    public:
        PairIterator(std::vector<Particle>::size_type outer, std::vector<Particle>::size_type inner, std::vector<Particle>& vec);
        std::pair<Particle&, Particle&> operator*() const;
        PairIterator& operator++();
        friend bool operator==(const PairIterator& a, const PairIterator& b);
        friend bool operator!=(const PairIterator& a, const PairIterator& b);
    };
};


#endif //PSEMOLDYN_PARTICLECONTAINER_H
