/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "ParticleWriter.h"

#include <fstream>
#include <list>

namespace outputWriter {

    class XYZWriter : public ParticleWriter {

    public:
        XYZWriter();
        ~XYZWriter();
        void plotParticles(std::vector<Particle> &particleVector, const std::string &filename, int iteration) override;
    };

} // namespace outputWriter
