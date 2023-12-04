#pragma once

#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "../src/IO/input/XMLReader.h"
#include "../src/Particles/DirectSumContainer.h"
#include "../src/IO/input/SimParameters.h"

class XMLReaderTest : public testing::Test {
protected:
    std::string filename;
    DirectSumContainer expectedContainer;
    std::shared_ptr<DirectSumContainer> receivedContainer = std::make_shared<DirectSumContainer>();
    SimParameters receivedSimParameters;

    void SetUp() override;
};
