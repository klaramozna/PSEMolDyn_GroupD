#include "XMLReaderTest.h"
#include "../src/utils/CuboidGenerator.h"

#include <string>

void XMLReaderTest::SetUp() {
    filename = "../../test/resources/";
    expectedContainer.getParticleVector().clear();
    receivedContainer.getParticleVector().clear();
};

/**
 * @brief read a valid XML file that specifies sim arguments and generates a cuboid
 * @result sim arguments should match and cuboid should match in size and composition with hardcoded simpleCube
 **/
TEST_F(XMLReaderTest, TestSimple1XMLReader) {
    // Initialize expected CuboidMock
    CuboidGenerator simpleCube(
            {0.0, 0.0, 0.0},
            40,8,1,
            1.1225,
            1.0,
            {0.0, 0.0, 0.0});
    XMLReader xmlreader;

    filename.append("simpleCuboid.xml");
    xmlreader.readFile(receivedContainer, filename, receivedSimParameters);

    expectedContainer = simpleCube.generateParticles();

    ASSERT_EQ(expectedContainer.getSize(), receivedContainer.getSize()) << "Containers didn't match in size";

    auto it1 = expectedContainer.begin();
    auto it2 = receivedContainer.begin();

    for (; it1 != expectedContainer.end() && it2!= receivedContainer.end(); ++it1, ++it2) {
        Particle p1 = *it1;
        Particle p2 = *it2;

        ASSERT_TRUE(p1 == p2) << "Expected " << p1.toString() << "\nReceived " << p2.toString();
    }
    //input_path and mode are empty strings here as they are passed explicitly in the test and not via command line
    SimParameters expectedSimParameters (5, 0.0002, 0.1, false, 2, "", "", "lennard", 1, 5, "MD_vtk");
    ASSERT_EQ(expectedSimParameters, receivedSimParameters) << "Simulation Parameters didn't match"; 

};

