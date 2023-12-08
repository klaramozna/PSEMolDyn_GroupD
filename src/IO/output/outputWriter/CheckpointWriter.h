//
// Created by RayenManai on 08.12.23.
//

#pragma once
#include "../../xsdCode/checkpointFormat.h"
#include "../../../Particles/ParticleContainer.h"

class CheckpointWriter {
public:
    /**
     * @brief Creates a CuboidGenerator object initializing it with the given parameters
     * @param 
     */
    CheckpointWriter();

    void writeCheckpoint (ParticleContainer &container);

    ~CheckpointWriter();
};
