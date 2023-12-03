/*
 * ParticleWriter.h
 *
 *  Created on: 07.11.2023
 *      Author: rodff
 */

#pragma once
#include "../../../Particles/DirectSumContainer.h"

class ParticleWriter {
public:
    virtual ~ParticleWriter() = default;
    virtual void plotParticles(std::vector<Particle> &particleVector, const std::string &filename,
                               int iteration) = 0;
};

