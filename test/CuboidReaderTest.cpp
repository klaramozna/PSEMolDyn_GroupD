//
// Created by rodff on 14.11.23.
//

#pragma once

#include "CuboidReaderTest.h"
#include "../src/CuboidGenerator.h"
#include <string>

void CuboidReaderTest::SetUp() {
    filename = "../../test/resources/";
    expectedContainer.getParticleVector().clear();
    receivedContainer.getParticleVector().clear();
};

/**
 * Try to read a valid Cuboid read from an input file
 * @result Cuboid should match in size and composition with hardcoded simpleCube
 **/
TEST_F(CuboidReaderTest, TestSimple1Cuboid) {
    // Initialize expected CuboidMock
    CuboidGenerator simpleCube(
            {0.0, 0.0, 0.0},
            3,3,3,
            0.1,
            10.0,
            {1.0, 0.0, 0.0});
    CuboidReader reader;

    filename.append("simpleCuboid.txt");
    reader.readFile(receivedContainer, filename);

    expectedContainer = simpleCube.generateParticles();

    ASSERT_EQ(expectedContainer.getSize(), receivedContainer.getSize()) << "Containers didn't match in size";

    auto it1 = expectedContainer.begin();
    auto it2 = receivedContainer.begin();

    for (; it1 != expectedContainer.end() && it2!= receivedContainer.end(); ++it1, ++it2) {
        Particle p1 = *it1;
        Particle p2 = *it2;

        ASSERT_TRUE(p1 == p2) << "Expected " << p1.toString() << "\nReceived " << p2.toString();
    }
};

TEST_F(CuboidReaderTest, TestEmptyFile) {
    CuboidReader reader;
    filename.append("empty.txt");


    ASSERT_EXIT(
        {
            reader.readFile(receivedContainer, filename);
        },
        ::testing::ExitedWithCode(-1),
        "Expected exit code is -1");
};

TEST_F(CuboidReaderTest, TestOneWrongCuboid) {
    CuboidReader reader;
    filename.append("oneWrongCuboid.txt");

    ASSERT_EXIT(
            {
                reader.readFile(receivedContainer, filename);
            },
            ::testing::ExitedWithCode(-1),
            "Expected exit code is -1");
};

TEST_F(CuboidReaderTest, TestTooManyRows) {

};

TEST_F(CuboidReaderTest, TestTwoCorrectCuboids) {

};

TEST_F(CuboidReaderTest, TestTwoWrongCuboids) {

};

