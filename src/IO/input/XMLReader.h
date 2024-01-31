/*
 * XMLReader.h
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#pragma once

#include "../../Particles/DirectSumContainer.h"
#include "SimParameters.h"

#include <array>
#include <memory>

class XMLReader{

public:
    XMLReader();
    virtual ~XMLReader();
    
     /**
     * @brief Reads a defined XML file containing the simulation arguments 
     * @param filename Input file
     * @param simParamteres instance of SimParameters class to store the simulation arguments read from the file
     * */
    void readFile (std::string &filename, SimParameters& simParameters);

    std::vector<std::shared_ptr<Particle>> getParticles () {
        return particles;
    }

private: 
    std::vector<std::shared_ptr<Particle>> particles;
};