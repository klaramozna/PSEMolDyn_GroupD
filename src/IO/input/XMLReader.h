/*
 * XMLReader.h
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#pragma once

#include "ParticleReader.h"
#include "../../Particles/ParticleContainer.h"
#include "SimParameters.h"

#include <array>

class XMLReader : public ParticleReader  {

public:
    XMLReader();
    virtual ~XMLReader();
   
    void readFile (ParticleContainer &container, std::string &filename, SimParameters& simParameters) override;
};