/*
 * ParticleWriter.h
 *
 *  Created on: 07.11.2023
 *      Author: rodff
 */

#pragma once
#include "../../../Particles/ParticleContainer.h"

class ParticleWriter {
public:
    virtual ~ParticleWriter() = default;
    virtual void plotParticles(ParticleContainer& container, const std::string &filename,
                       int iteration) = 0;
};

