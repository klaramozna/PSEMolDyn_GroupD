//
// Created by rodff on 14.11.23.
//

#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/CuboidReader.h"
#include "../src/CuboidMock.h"
#include "../src/ParticleContainer.h"

class CuboidReaderTest : public testing::Test {
protected:
    std::vector<CuboidMock> cuboids;
    std::vector<CuboidMock> expecteds;
    std::string filename;
    ParticleContainer dummy;

    void SetUp() override;
};
