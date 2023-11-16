/* File IO */
#include "FileReader.h"
#include "CuboidReader.h"
#include "ParticleReader.h"

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

/* Standard IO */
#include <iostream>

/* Simulation Logic */
#include "Simulation.h"
#include "ParticleContainer.h"
#include "GravitationalForce.h"
#include "LennardJones.h"

/* Logging */
#include "Logger.h"
#include <CL.h>

/* Generators for Particles */
#include "ParticleGenerator.h"
#include "CuboidGenerator.h"

constexpr double start_time = 0;

const double sigma = 1;
const double epsilon = 5;


double end_time;
double delta_t;
double averageVelo;

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

    int status = cl.parse_arguments(argc, argsv, end_time, delta_t, log_level, input_path, input_mode, force);
    
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

    averageVelo = 0.1;
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
