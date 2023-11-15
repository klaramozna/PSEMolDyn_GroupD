#pragma once

#include <gtest/gtest.h>
#include "../src/LennardJones.h"
#include "../src/LennardJones.h" 
#include "../src/Particle.h" 
#include "../src/VectorDouble3.h" 

class LennardJonesTest : public testing::Test {
protected:
   
    LennardJones lennardJones{5,1};
};
