//
// Created by rodff on 14.11.23.
//

#pragma once

#include "CuboidReaderTest.h"
#include <string>

void CuboidReaderTest::SetUp() {
    this->cuboids.clear();
    this->expecteds.clear();
    filename = "../../test/resources/";
};

TEST_F(CuboidReaderTest, TestSimple1Cuboid) {
    // Initialize expected CuboidMock
    CuboidMock simpleCube(
            {0.0, 0.0, 0.0},
            {3,3,3},
            {0.1, 0.1, 0.1},
            10.0,
            {1.0, 0.0, 0.0});

    expecteds.push_back(simpleCube);

    // Receive actual file
    filename.append("simpleCuboid.txt");

    CuboidReader reader;
    reader.readFile(dummy, filename);

    // Make sure sizes match
    if (expecteds.size() != cuboids.size()) {
        FAIL() << "Didn't receive expected amount of cuboids";
    }

    auto it1 = expecteds.begin();
    auto it2 = cuboids.begin();

    // Compare each cuboid making sure they match
    for (; it1 != expecteds.end(); ++it1, ++it2) {
        CuboidMock expected = *it1;
        CuboidMock received = *it2;
        EXPECT_EQ(expected, received);
    }
};

TEST_F(CuboidReaderTest, TestEmptyFile) {

};

TEST_F(CuboidReaderTest, TestOneWrongCuboid) {

};

TEST_F(CuboidReaderTest, TestTooManyRows) {

};

TEST_F(CuboidReaderTest, TestTwoCorrectCuboids) {

};

TEST_F(CuboidReaderTest, TestTwoWrongCuboids) {

};

