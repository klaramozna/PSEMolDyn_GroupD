/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "ParticleReader.h"
#include "../../Particles/DirectSumContainer.h"

#include <array>

class FileReader : public ParticleReader  {

public:
    FileReader();
    virtual ~FileReader();
    DirectSumContainer readFile(std::string &filename) override;
};
