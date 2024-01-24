#ifndef PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H
#define PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H

#include "Boundary.h"


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
     * @brief Returns the bin index of the particle. The bins start at the top of the domain.
     * @param p Particle to be used for the calculation.
     * @return Index of the corresponding bin.
     */
    int getBinIndex(const Particle& p);
};


#endif //PSEMOLDYN_GROUPD_PARTICLESTATISTICS_H
