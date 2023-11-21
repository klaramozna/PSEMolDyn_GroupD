//
// Created by rodff on 14.11.23.
//

#include "CuboidReaderTest.h"
#include "../src/utils/CuboidGenerator.h"

#include <string>
#include <regex>

void CuboidReaderTest::SetUp() {
    filename = "../../test/resources/";
    expectedContainer.getParticleVector().clear();
    receivedContainer.getParticleVector().clear();
};

/**
 * @brief Try to read a valid Cuboid read from an input file
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
/**
 * @brief Test whether an empty file causes an exception
 * @result An exception containing "No line found - empty file" in the error message
 * */
TEST_F(CuboidReaderTest, TestEmptyFile) {
    CuboidReader reader;
    DirectSumContainer container;
    filename.append("empty.txt");

    try {
        reader.readFile(container, filename);
        FAIL() << "Expected std::runtime_error, but no exception was thrown.";
    } catch (const std::runtime_error& ex) {
        // Check the error message
        EXPECT_STREQ(ex.what(), "No line found - empty file");
    } catch (...) {
        FAIL() << "Expected std::runtime_error, but a different exception was thrown.";
    }
};

/**
 * @brief Test whether the parseLine() in CuboidReader throws an exception for an invalid line
 * @result An exception containing "Invalid line format - " should be caught
 * */
TEST_F(CuboidReaderTest, TestOneWrongCuboid) {
    CuboidReader reader;
    DirectSumContainer container;
    filename.append("tooLittleRows.txt");

    try {
        reader.readFile(container, filename);
        FAIL() << "Expected std::runtime_error, but no exception was thrown.";
    } catch (const std::runtime_error& ex) {
        // Check the error message
        std::regex pattern(R"(^Invalid line format - )");
        EXPECT_TRUE(std::regex_search(ex.what(), pattern));
    } catch (...) {
        FAIL() << "Expected std::runtime_error, but a different exception was thrown.";
    }
};

/**
 * @brief Test whether too many rows per line get caught as an exception
 * @result An exception containing "Invalid line format - " should be caught
 * */
TEST_F(CuboidReaderTest, TestTooManyRows) {
    CuboidReader reader;
    DirectSumContainer container;
    filename.append("tooManyRows.txt");

    try {
        reader.readFile(container, filename);
        FAIL() << "Expected std::runtime_error, but no exception was thrown.";
    } catch (const std::runtime_error& ex) {
        // Check the error message
        std::regex pattern(R"(^Invalid line format - )");
        EXPECT_TRUE(std::regex_search(ex.what(), pattern));
    } catch (...) {
        FAIL() << "Expected std::runtime_error, but a different exception was thrown.";
    }
};

/**
 * @brief Try to read two Cuboids read from an input file
 * @result Cuboid should match in size and composition with hardcoded cubes
 **/
TEST_F(CuboidReaderTest, TestTwoCorrectCuboids) {
// Initialize expected CuboidMock
    CuboidGenerator firstCube(
            {0.0, 0.0, 0.0},
            3,3,3,
            0.1,
            10.0,
            {1.0, 0.0, 0.0});

    CuboidGenerator secondCube(
            {-10.0, -10.0, 0.0},
            4,4,4,
            1.5,
            10.0,
            {0.0, -1.0, 0.0});

    CuboidReader reader;

    filename.append("twoCuboids.txt");
    reader.readFile(receivedContainer, filename);

    expectedContainer = firstCube.generateParticles();
    expectedContainer.addParticles(secondCube.generateParticles());

    ASSERT_TRUE(expectedContainer.getSize() == receivedContainer.getSize()) << "Containers didn't match in size";

    auto it1 = expectedContainer.begin();
    auto it2 = receivedContainer.begin();

    for (; it1 != expectedContainer.end() && it2!= receivedContainer.end(); ++it1, ++it2) {
        Particle p1 = *it1;
        Particle p2 = *it2;

        ASSERT_TRUE(p1 == p2) << "Expected " << p1.toString() << "\nReceived " << p2.toString();
    }
};
