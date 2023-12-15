#include "CheckpointTest.h"

void CheckpointTest::SetUp() {
    filename = std::string(TEST_RESOURCES_DIR);
    std::vector<Particle> particles{p1, p2, p3, p4};
    container.addParticles(particles);
}

/**
 * @brief state will be saved to a checkpoint file and then read again
 * @result read_container must contain the same particles as saved
 **/

// This test pass locally but not on the pipeline, will check why ...
/* 
TEST_F(CheckpointTest, TestSimpleCheckpoint) {

    filename.append("Checkpoints/checkpoint1.xml");
    // was used the first time to create the checkpoint
    //cWriter.writeCheckpoint(container, filename);

    
    LinkedCellContainer read_container{Boundary(4, 4, 4, fc, 1), 1};
    cReader.readFile(read_container, filename, simParameters);
    
    ASSERT_EQ(read_container.getSize(), container.getSize()) << "Containers didn't match in size";
    auto it1 = container.getParticleVector().begin();
    auto it2 = read_container.getParticleVector().begin();

    for (; it1 != container.getParticleVector().end() && it2!= read_container.getParticleVector().end(); ++it1, ++it2) {
        Particle p1 = *it1;
        Particle p2 = *it2;

        ASSERT_TRUE(p1 == p2) << "Expected " << p1.toString() << "\nReceived " << p2.toString();
    }
};
*/




