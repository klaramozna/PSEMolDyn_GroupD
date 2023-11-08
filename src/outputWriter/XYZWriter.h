/*
 * XYZWriter.h
 *
 *  Created on: 01.03.2010
 *      Author: eckhardw
 */

#pragma once

#include "outputWriter/ParticleWriter.h"

#include <fstream>
#include <list>

namespace outputWriter {

    class XYZWriter : public ParticleWriter {

    public:
        XYZWriter();
        ~XYZWriter();

        void plotParticles(ParticleContainer &container, const std::string &filename,
                           int iteration) override;
    };

} // namespace outputWriter
