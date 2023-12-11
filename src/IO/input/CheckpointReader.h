/*
 * CheckpointReader.h
 *
 *  Created on: 11.12.2023
 *      Author: RayenManai
 */

#pragma once

#include "ParticleReader.h"
#include "../../Particles/ParticleContainer.h"
#include "SimParameters.h"

#include <array>

class CheckpointReader : public ParticleReader  {

public:
    CheckpointReader();
    virtual ~CheckpointReader();
    
     /**
     * @brief Reads a defined XML file containing the simulation arguments 
     * @param container ParticleContainer that will receive the read-in particles
     * @param filename Input file
     * @param simParamteres instance of SimParameters class to store the simulation arguments read from the file
     * */
    void readFile (ParticleContainer &container, std::string &filename, SimParameters& simParameters) override;
};