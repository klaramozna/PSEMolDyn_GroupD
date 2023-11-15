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

/* Logging */
#include "Logger.h"


#include <CL.h>

#include "ParticleGenerator.h"
#include "CuboidGenerator.h"

constexpr double start_time = 0;
double end_time;
double delta_t;
int log_level;
std::string input_path;
std::string input_mode;


int main(int argc, char *argsv[]) {
    CuboidGenerator c(std::array<double, 3>{0, 0,  0}, 2, 1, 2, 1, 1, std::array<double, 3>{0, 0,  0});
    ParticleContainer cont = c.generateParticles();
    for(auto & p : cont){
        p.getXVector().print();
    }
    
    CL cl;
    int status = cl.parse_arguments(argc, argsv, end_time, delta_t, log_level, input_path, input_mode);
    
    //any error in parsing
    if (status) {
        return 1;
    }

    FileReader fileReader;

    GravitationalForce gravForce;
    ParticleContainer container;

    outputWriter::VTKWriter writer;

    Simulation simulation(delta_t, container, gravForce);

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

        Logger::console->info("Iteration {} finished.", iteration);

        current_time += delta_t;
    }

    Logger::console->info("Output written. Terminating...");
    return 0;
}
