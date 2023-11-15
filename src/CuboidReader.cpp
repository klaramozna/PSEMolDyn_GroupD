#include "CuboidReader.h"
#include "CuboidGenerator.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Logger.h"

void CuboidReader::readFile(ParticleContainer &container, std::string &filename) {
    int numberOfCuboids = 0;

    std::array<double, 3> llc;
    int nx, ny, nz;
    double distance;
    std::array<double, 3> velocity;
    double mass;

    std::ifstream input_file(filename);
    std::string line;

    if (input_file.is_open()) {
        // Fetch number of cuboids
        getline(input_file, line);
        Logger::console->info("Read line: {} ", line);

        // Ignore comments or blank lines
        while (line.empty() or line[0] == '#') {
            getline(input_file, line);
        }

        // Get number of cuboids
        std::istringstream numstream(line);
        numstream >> numberOfCuboids;
        Logger::console->info("Reading {} cuboids", numberOfCuboids);

        // Get next line before starting line processing
        getline(input_file, line);
        Logger::console->info("Read line: {} ", line);

        for (int i = 0; i < numberOfCuboids; i++) {
            std::istringstream iss(line);

            iss >> llc[0] >> llc[1] >> llc[2];
            iss >> nx >> ny >> nz;
            iss >> distance;
            iss >> mass;

            if (iss.eof()) {
                std::cout
                        << "Error reading file: eof reached unexpectedly reading from line "
                        << i << std::endl;
                exit(-1);
            }

            iss >> velocity[0] >> velocity[1] >> velocity[2];

            CuboidGenerator generator(llc,nx,ny,nz,distance,mass,velocity);
            ParticleContainer readContainer = generator.generateParticles();

            container.addParticles(readContainer);

            // Read next line
            getline(input_file, line);
            Logger::console->info("Read line: {} ", line);
        }
    } else {
        std::cout << "Error: could not open file " << filename << std::endl;
        exit(-1);
    }
}