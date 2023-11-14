#include "CuboidReader.h"
#include "CuboidMock.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Logger.h"

void CuboidReader::readFile(ParticleContainer &container, std::string &filename) {
    int numberOfCuboids = 0;
    std::array<double, 3> coordinate;
    std::array<int, 3> numParticles;
    std::array<double, 3> distance;
    std::array<double, 3> initialVelocity;

    double mass;

    std::ifstream input_file(filename);
    std::string tmp_string;

    if (input_file.is_open()) {
        // Fetch number of cuboids
        getline(input_file, tmp_string);
        Logger::console->info("Read line: {} ", tmp_string);

        // Ignore comments or blank lines
        while (tmp_string.empty() or tmp_string[0] == '#') {
            getline(input_file, tmp_string);
            Logger::console->info("Read line: {} ", tmp_string);
        }

        // Get number of cuboids
        std::istringstream numstream(tmp_string);
        numstream >> numberOfCuboids;
        Logger::console->info("Reading {} cuboids", numberOfCuboids);

        // Reserve space for all the cuboids -> Testing feature
        cuboids.reserve(numberOfCuboids);

        // Get next line before starting line processing
        getline(input_file, tmp_string);
        Logger::console->info("Read line: {} ", tmp_string);

        /* Read
         * 1. Lower left coordinate
         * 2. Number of particles per dimension
         * 3. Distance between particles per dimension
         * 4. Mass of particles
         * 5. Initial velocity (3 components)
         * */
        for (int i = 0; i < numberOfCuboids; i++) {
            std::istringstream datastream(tmp_string);

            // 1
            for (auto &xj: coordinate) {
                datastream >> xj;
            }

            // 2
            for (auto &nj: numParticles) {
                datastream >> nj;
            }

            // 3
            for (auto &dj: distance) {
                datastream >> dj;
            }

            // 4
            datastream >> mass;

            // 5
            for (auto &vj: initialVelocity) {
                datastream >> vj;
            }

            if (datastream.eof()) {
                Logger::err_logger->error("Error reading file: eof reached unexpectedly reading from line {}", i);
                exit(-1);
            }

            // Generate cuboid and place all new particles onto ParticleContainer
            cuboids.emplace_back(
                    coordinate,
                    numParticles,
                    distance,
                    initialVelocity,
                    mass
            );

            // Read next line
            getline(input_file, tmp_string);
            Logger::console->info("Read line: {} ", tmp_string);
        }
    } else {
        std::cout << "Error: could not open file " << filename << std::endl;
        exit(-1);
    }
}