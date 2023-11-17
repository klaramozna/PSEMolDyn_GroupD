#pragma once

#include <gtest/gtest.h>
#include "../src/Simulation/Physics/LennardJones.h"
#include "../src/Particles/Particle.h" 
#include "../src/utils/VectorDouble3.h" 

class LennardJonesTest : public testing::Test {
protected:
   
    LennardJones lennardJones{5,1};
};
