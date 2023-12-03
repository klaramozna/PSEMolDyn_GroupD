#include "CuboidReader.h"
#include "../../utils/CuboidGenerator.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <regex>
#include "../Logger.h"


void CuboidReader::readFile(ParticleContainer &container, std::string &filename) {
    std::ifstream inputFile(filename);
    std::string line;

    try {
        // Try to find file
        if (!inputFile.is_open()) {
            throw std::runtime_error("Could not open file " + filename);
        }

        // Make sure file is not empty
        if (!getline(inputFile, line)) {
            throw std::runtime_error("No line found - empty file");
        }

        Logger::console->info("Read line: {} ", line);

        // Ignore comments or blank lines
        while (line.empty() or line[0] == '#') {
            getline(inputFile, line);
        }

        // Find number of cuboids
        if (!parseNumberOfCuboids(line)) {
            throw std::runtime_error("Number of cuboids not found");
        }

        Logger::console->info("Reading {} cuboids", numberOfCuboids);

        for (int i = 0; i < numberOfCuboids; i++) {
            // Check for unexpected end of file after number of cuboids
            if (!getline(inputFile, line)) {
                throw std::runtime_error("Unexpected end of file before reading all cuboids!");
            }

            Logger::console->info("Read line: {} ", line);

            if (!validateLineFormat(line)) {
                throw std::runtime_error("Invalid line format - " + line);
            }

            CuboidGenerator generator = parseLine(line);
            container.addParticles(generator.generateParticles());
        }
    } catch (const std::exception &ex) {
        Logger::err_logger->error("Error: {}", ex.what());
        throw;
    }
}

bool CuboidReader::validateLineFormat(const std::string& line) {
    /*
     * Explanation of the pattern
     * We want to catch
     * 1. 3 doubles - llc
     * 2. 3 integer - numParticles
     * 3. 1 double - distance
     * 4. 1 double - mass
     * 5. 3 doubles - initialVelocity
     *
     * We can have arbitrarily many whitespaces in between each double and integer, so the basic structure is
     * \s+(CapturingGroupForEitherDoubleOrInteger)\s+(CapturingGroupForDoubleOrInteger) ....
     *
     * We then have for doubles
     * ([+-]?([0-9]*[.])?[0-9]+)
     * For integers
     * ([-+]?\d+)
     * */

    std::string doublePart = R"(([+-]?([0-9]*[.])?[0-9]+))";
    std::string integerPart = R"(([-+]?\d+))";

    std::string regexPattern =
            // LLC
            R"(^\s*)" + doublePart + R"(\s+)" + doublePart + R"(\s+)" + doublePart +
            // numParticles
            R"(\s+)" + integerPart + R"(\s+)" + integerPart + R"(\s+)" + integerPart +
            // distance
            R"(\s+)" + doublePart +
            // mass
            R"(\s+)" + doublePart +
            // velocity
            R"(\s*)" + doublePart + R"(\s+)" + doublePart + R"(\s+)" + doublePart + R"(\s*$)";

    std::regex pattern(regexPattern);
    return std::regex_match(line, pattern);
}

CuboidGenerator CuboidReader::parseLine(const std::string& line) {
    std::istringstream iss(line);

    std::array<double, 3> llc{};
    int nx, ny, nz;
    double distance;
    std::array<double, 3> velocity{};
    double mass;

    iss >> llc[0] >> llc[1] >> llc[2];
    iss >> nx >> ny >> nz;
    iss >> distance;
    iss >> mass;
    iss >> velocity[0] >> velocity[1] >> velocity[2];

    CuboidGenerator generator(llc, nx, ny, nz, distance, mass, velocity);
    return generator;
};

bool CuboidReader::parseNumberOfCuboids(const std::string& line) {
    std::istringstream iss(line);
    return (iss >> numberOfCuboids) && iss.eof();
}