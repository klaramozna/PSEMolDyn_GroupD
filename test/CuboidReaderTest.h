//
// Created by rodff on 14.11.23.
//

#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/CuboidReader.h"
#include "../src/ParticleContainer.h"

class CuboidReaderTest : public testing::Test {
protected:
    std::string filename;
    ParticleContainer expectedContainer;
    ParticleContainer receivedContainer;

    void SetUp() override;
};
