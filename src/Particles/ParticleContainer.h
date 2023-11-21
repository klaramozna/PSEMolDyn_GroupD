//
// Created by klara on 21.11.23.
//

#ifndef PSEMOLDYN_GROUPD_PARTICLECONTAINER_H
#define PSEMOLDYN_GROUPD_PARTICLECONTAINER_H


#include <functional>
#include "Particle.h"

class ParticleContainer {
public:
    /**
     * @brief Adds the given particle to the container.
     * @param p The particle to be added.
     */
    virtual void addParticle(const Particle& p) = 0;

    /**
     * @brief Adds the given particles to the container.
     * @param toAdd The vector containing the particles to be added.
     */
    void addParticles(const std::vector<Particle>& toAdd);

    /**
     * @brief Returns the number of particles in the container.
     * @return The number of particles in the container.
     */
    virtual size_t getSize() = 0;

    /**
     * @brief Applies the given function to all particles.
     * @param function Function that is applied to each particle.
     */
    virtual void applyToAll(const std::function<void(Particle&)>& function) = 0;

    /**
     * @brief Applies the given function to pairs of particles (different pairs depending on implementation).
     * @param function The function to be applied to each pair.
     */
    virtual void applyToPairs(const std::function<void(Particle&, Particle&)>& function) = 0;

    /**
     * @brief Returns a vector of all particles in the container.
     * @return The vector with the particles of the container.
     */
    virtual std::vector<Particle>& getParticleVector() = 0;

    /**
     * @brief Destroys the ParticleContainer object.
     */
    virtual ~ParticleContainer() = default;
};


#endif //PSEMOLDYN_GROUPD_PARTICLECONTAINER_H
