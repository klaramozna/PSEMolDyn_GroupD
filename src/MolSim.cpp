/* File IO */
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

/* Standard IO */
#include <iostream>

/* Boost */
#include <boost/program_options.hpp>
#include <filesystem>

/* Simulation Logic */
#include "Simulation.h"
#include "ParticleContainer.h"
#include "GravitationalForce.h"

/* Logging*/
#include <spdlog/spdlog.h>

#include <CL.h>

constexpr double start_time = 0;
double end_time;
double delta_t;
int log_level;
std::string input_path;


int main(int argc, char *argsv[]) {
    
    CL cl;
    int status = cl.parse_arguments(argc, argsv, end_time, delta_t, log_level, input_path);
    
    //any error in parsing
    if (status) {
        return 1;
    }

    FileReader fileReader;

    GravitationalForce gravForce;
    ParticleContainer container;

    outputWriter::VTKWriter writer;

    Simulation simulation(delta_t, container, &gravForce);

    fileReader.readFile(simulation.getParticles(), input_path);

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

        std::cout << "Iteration " << iteration << " finished." << std::endl;

        current_time += delta_t;
    }

    //console_logger->info("Output written. Terminating...");
    return 0;
}
