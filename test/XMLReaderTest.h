#pragma once

#include <gtest/gtest.h>
#include <string>

#include "../src/IO/input/XMLReader.h"
#include "../src/Particles/LinkedCellContainer.h"
#include "../src/IO/input/SimParameters.h"

class XMLReaderTest : public testing::Test {
protected:
    std::string filename;
    DirectSumContainer expectedContainer;
    DirectSumContainer receivedContainer;
    SimParameters receivedSimParameters;

    void SetUp() override;
};
