/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "ParticleReader.h"
#include "../../Particles/ParticleContainer.h"

#include <array>

class FileReader : public ParticleReader  {

public:
    FileReader();
    virtual ~FileReader();
    void readFile(ParticleContainer &container, std::string &filename) override;
};
