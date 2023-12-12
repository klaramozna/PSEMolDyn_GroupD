//
// Created by RayenManai on 08.12.23.
//

#pragma once
#include "../../xsdCode/checkpointFormat.h"
#include "../../../Particles/ParticleContainer.h"

class CheckpointWriter {
public:
    /**
     * @brief Constructor: Creates a CheckpointWriter
     */
    CheckpointWriter();

    /**
     * @brief writes the whole particles state to a given file in XML format
     * @param container the container with the particles of the simulation to store
     * @param filename the path of the output file
     */
    void writeCheckpoint (ParticleContainer &container, std::string filename);

     /**
     * @brief Destructor
     */
    ~CheckpointWriter();
};
