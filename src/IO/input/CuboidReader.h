#pragma once

#include "ParticleReader.h"
#include "../../utils/CuboidGenerator.h"

class CuboidReader : public ParticleReader {
public:
    ~CuboidReader() = default;
    /**
     * @brief Reads a file containing data to generate multiple cuboids and dumps the cuboids onto the container
     * @param container DirectSumContainer that will receive the read-in particles
     * @param filename Input file
     * */
    void readFile(DirectSumContainer &container, std::string &filename) override;

private:
    int numberOfCuboids{};

    /**
     * @brief Validates the read-in line according to the template specification with a regex pattern
     * @param line Line to be validated
     * @return Bool representing whether the line was accepted
     * */
    static bool validateLineFormat(const std::string& line);

    /**
     * @brief Read the line in and transform it to a CuboidGenerator after validation
     * @param line Line to be parsed in
     * @return Returns the induced CuboidGenerator
     * */
    static CuboidGenerator parseLine(const std::string& line);

    /**
     * @brief Reads the number of cuboids in and writes to numberOfParticles
     * @param line Line to be parsed
     * @return Bool representing failure or success of parsing the number of cuboids
     * */
    bool parseNumberOfCuboids(const std::string& line);
};