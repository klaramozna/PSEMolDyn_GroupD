//
// Created by rodff on 14.11.23.
//

#pragma once

#include <gtest/gtest.h>
#include <string>
#include <memory>

#include "../src/IO/input/CuboidReader.h"
#include "../src/Particles/DirectSumContainer.h"

class CuboidReaderTest : public testing::Test {
protected:
    std::string filename;
    DirectSumContainer expectedContainer;
    std::shared_ptr<DirectSumContainer> receivedContainer_ptr = std::make_shared<DirectSumContainer>();

    void SetUp() override;
};
