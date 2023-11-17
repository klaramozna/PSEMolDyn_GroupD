/* File IO */
#include "IO/input/FileReader.h"
#include "IO/input/CuboidReader.h"
#include "IO/input/ParticleReader.h"

#include "IO/output/outputWriter/XYZWriter.h"
#include "IO/output/outputWriter/VTKWriter.h"

/* Standard IO */
#include <iostream>

/* Simulation Logic */
#include "Simulation/Simulation.h"
#include "Particles/ParticleContainer.h"
#include "Simulation/Physics/GravitationalForce.h"
#include "Simulation/Physics/LennardJones.h"

/* Logging */
#include "IO/Logger.h"
#include <IO/CLparser/CL.h>

/* Generators for Particles */
#include "Particles/ParticleGenerator.h"
#include "utils/CuboidGenerator.h"

constexpr double start_time = 0;

const double sigma = 1;
const double epsilon = 5;


double end_time;
double delta_t;
double averageVelo;

bool testing;

int log_level;
std::string input_path;
std::string input_mode;
std::string force;


int main(int argc, char *argsv[]) {
    CL cl;
    std::unique_ptr<ParticleReader> reader;
    std::unique_ptr<ForceCalculation> forceCalculation;

    ParticleContainer container;

    outputWriter::VTKWriter writer;

    int status = cl.parse_arguments(argc, argsv, end_time, delta_t, log_level, input_path, input_mode, force, averageVelo, testing);
    
    //any error in parsing
    if (status) {
        return 1;
    }

    if (force == "lennard") {
        forceCalculation = std::make_unique<LennardJones>(epsilon, sigma);
    }

    if (force == "grav") {
        forceCalculation = std::make_unique<GravitationalForce>();
    }

    Simulation simulation(delta_t, container, *forceCalculation, averageVelo);


    if (input_mode == "cuboid") {
        reader = std::make_unique<CuboidReader>();
    }

    if (input_mode == "particle") {
        reader = std::make_unique<FileReader>();
    }

    if (!reader) {
        Logger::err_logger->error("Reader was not correctly initialized");
        exit(-1);
    }

    reader->readFile(simulation.getParticles(), input_path);

    int iteration = 0;
    double current_time = start_time;
    std::string out_name("MD_vtk");

    // This is ugly and shouldn't be in main, but it is for a later refactor
    if (testing) {
        auto measure_start_time = std::chrono::high_resolution_clock::now();

        while (current_time < end_time) {
            simulation.runIteration();
            iteration++;
            current_time += delta_t;
        }

        auto measure_end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(measure_end_time - measure_start_time);

        Logger::console->info("Time taken: {} milliseconds", duration.count());
    } else {
        // for this loop, we assume: current x, current f and current v are known
        while (current_time < end_time) {
            simulation.runIteration();

            iteration++;
            if (iteration % 10 == 0) {
                writer.plotParticles(simulation.getParticles(), out_name, iteration);
            }

            Logger::console->info("Iteration {} finished.", iteration);

            current_time += delta_t;
        }

        Logger::console->info("Output written. Terminating...");
        return 0;
    }
}
