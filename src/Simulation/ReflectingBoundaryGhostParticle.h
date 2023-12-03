//
// Created by rodff on 23.11.23.
//

#pragma once
#include "ReflectingBoundary.h"

class ReflectingBoundaryGhostParticle : public ReflectingBoundary {
public:
    void processBoundary(LinkedCellContainer &container) override;
};