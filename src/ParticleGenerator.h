#ifndef PSEMOLDYN_GROUPD_PARTICLEGENERATOR_H
#define PSEMOLDYN_GROUPD_PARTICLEGENERATOR_H

#include "ParticleContainer.h"
#include "Particle.h"

class ParticleGenerator {
public:
    /**
     * @brief Constructor that default initializes the particle vector.
     */
    ParticleGenerator() = default;

    /**
     * @brief Generates particles.
     * @return A particle container with the generated particles.
     */
    virtual ParticleContainer generateParticles() = 0;

    /**
     * @brief Destroys a ParticleGenerator object (allows deleting a pointer to ParticleGenerator without memory leaks).
     */
    virtual ~ParticleGenerator()= default;

protected:
    /**
     * @brief Stores the generated particles.
     */
    std::vector<Particle> particles;
};


#endif //PSEMOLDYN_GROUPD_PARTICLEGENERATOR_H
