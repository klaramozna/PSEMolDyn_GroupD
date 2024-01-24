//
// Created by klara on 24.01.24.
//

#include "ParticleStatistics.h"

ParticleStatistics::ParticleStatistics(Boundary boundary, int n, int frequency): boundary{0, 0, 0, 0, {}} {
    this->n = n;
    this->boundary = boundary;
    this->frequency = frequency;
    currentIteration = 0;
    binVolume = (boundary.getDimensions()[0] * boundary.getDimensions()[1] * boundary.getDimensions()[2]) / n;
}

void ParticleStatistics::calculateStatistics(const std::vector<Particle> &particles) {
    if(currentIteration % frequency == 0){
        // Array of bins. The first part of the pair is the bin velocity average. The second part is the density average
        std::vector<std::pair<VectorDouble3, double>> bins;
        bins.resize(n, std::pair<VectorDouble3, double>{VectorDouble3(), 0});

        // Calculating the total sum of all velocities and total number of particles in each bin
        for(auto const & p : particles){
            if(boundary.isInside(p)){
                bins[getBinIndex(p)].first += p.getVVector();
                bins[getBinIndex(p)].second++;
            }
        }

        // Calculating the final averages from the total values
        for(auto & bin : bins){
            bin.first = (1 / bin.second) * bin.first;
            bin.second = bin.second / binVolume;
        }
    }
    currentIteration++;
}

int ParticleStatistics::getBinIndex(const Particle &p) {
    double distanceFromTom = boundary.getDimensions()[1] - p.getX()[1];
    double binHeight = boundary.getDimensions()[1] / n;
    return static_cast<int>(distanceFromTom / binHeight);
}
