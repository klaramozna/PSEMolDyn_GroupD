#ifndef PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H
#define PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H

#include "Boundary.h"
#include <fstream>


class ParticleStatistics {
public:

    /**
     * @brief Creates a ParticleStatistics object using the given parameters.
     * @param boundary The boundary of the simulation.
     * @param n The number of bins (vertically).
     * @param frequency How often the statistics should be calculated. For example if frequency is 5, the statistics are calculated every 5 iterations.
     */
    ParticleStatistics(Boundary boundary, int n, int frequency);

    /**
     * @brief Calculates the average velocity and density for each bin and writes those to the csv file.
     */
    void calculateStatistics(const std::vector<Particle>& particles);

    /**
     * @brief Makes sure the file is closed correctly.
     */
    ~ParticleStatistics();

    /**
     * @brief Returns a vector containing the average velocity and density of each bin from top to bottom. Primarily for testing purposes.
     * @param particles Particles that the statistics should be calculated on.
     * @return The statistics for each bin top to bottom of the domain. First component of the pair is average velocity, the second density.
     */
    std::vector<std::pair<VectorDouble3, double>> calculateStatisticsTest(const std::vector<Particle>& particles);

private:

    /**
     * @brief Number of bins (vertically)
     */
    int n;

    /**
     * @brief The boundary of the domain
     */
    Boundary boundary;

    /**
     * @brief Number of iterations, per which the statistics should be calculated.
     */
    int frequency;

    /**
     * @brief Current iteration in the simulation.
     */
    int currentIteration;

    /**
     * @brief Volume of one bin.
     */
    double binVolume;

    /**
     * @brief Stream for outputting the statistics.
     */
    std::ofstream outputFile{};

    /**
     * @brief Returns the bin index of the particle. The bins start at the top of the domain.
     * @param p Particle to be used for the calculation.
     * @return Index of the corresponding bin.
     */
    int getBinIndex(const Particle& p);

    /**
     * @brief Writes the statistics to a file.
     * @param bins The average velocity and density of each bin.
     */
    void outputStatistics(const std::vector<std::pair<VectorDouble3, double>>& bins);
};


#endif //PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H
