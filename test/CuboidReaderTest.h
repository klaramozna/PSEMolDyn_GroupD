//
// Created by rodff on 14.11.23.
//

#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/IO/input/CuboidReader.h"
#include "../src/Particles/DirectSumContainer.h"
#include "../src/IO/input/SimParameters.h"

class CuboidReaderTest : public testing::Test {
protected:
    std::string filename;
    DirectSumContainer expectedContainer;
    DirectSumContainer receivedContainer;
    SimParameters simParameters;

    void SetUp() override;
};
