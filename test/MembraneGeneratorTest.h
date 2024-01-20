#pragma once

#include <gtest/gtest.h>
#include "../src/utils/MembraneGenerator.h"

class MembraneGeneratorTest : public testing::Test {
protected:
    MembraneGenerator generator{std::array<double, 3>{0, 0, 0}, 3, 3, 1, 1, 1, std::array<double, 3>{0}, 1.2, 2, 500, 2.2, {}};
};


