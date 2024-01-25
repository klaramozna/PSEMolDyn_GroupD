
#include "ParticleStatistics.h"
#include <stdexcept>
#include <string>

ParticleStatistics::ParticleStatistics(Boundary boundary, int n, int frequency): boundary{0, 0, 0, 0, {}} {
    this->n = n;
    this->boundary = boundary;
    this->frequency = frequency;
    currentIteration = 0;
    binVolume = (boundary.getDimensions()[0] * boundary.getDimensions()[1] * boundary.getDimensions()[2]) / n;
    outputFile.open("../particle_statistics.csv");
    if(!outputFile.is_open()){
        throw std::ios_base::failure("File could not be opened.");
    }
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
        for(auto & bin : bins) {
            bin.first = (1 / bin.second) * bin.first;
            bin.second = bin.second / binVolume;
        }

        outputStatistics(bins);
    }
    currentIteration++;
}

int ParticleStatistics::getBinIndex(const Particle &p) {
    double distanceFromTom = boundary.getDimensions()[1] - p.getX()[1];
    double binHeight = boundary.getDimensions()[1] / n;
    return static_cast<int>(distanceFromTom / binHeight);
}

ParticleStatistics::~ParticleStatistics() {
    outputFile.close();
}

void ParticleStatistics::outputStatistics(const std::vector<std::pair<VectorDouble3, double>> &bins) {
    std::string iteration = "iteration_" + std::to_string(currentIteration);

    for(int i = 0; i < bins.size(); i++){
        std::string binNr = "bin_" + std::to_string(i);
        std::string avgVelo = std::to_string(bins[i].first.convertToArray()[0]) + "|" + std::to_string(bins[i].first.convertToArray()[1]) + "|" + std::to_string(bins[i].first.convertToArray()[2]);
        std::string density = std::to_string(bins[i].second);
        outputFile << (iteration + "-" + binNr + "-" + "velocity:" + avgVelo + ",");
        outputFile << (iteration + "-" + binNr + "-" + "density:" + density + ",");
    }
}
