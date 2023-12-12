/* File IO */
#include "IO/input/FileReader.h"
#include "IO/input/CuboidReader.h"
#include "IO/input/ParticleReader.h"

#include "IO/output/outputWriter/XYZWriter.h"
#include "IO/output/outputWriter/VTKWriter.h"

#include "IO/input/SimParameters.h"
#include "IO/input/XMLReader.h"

/* Standard IO */
#include <iostream>

/* Simulation Logic */
#include "Simulation/Simulation.h"
#include "Particles/LinkedCellContainer.h"
#include "Simulation/Physics/GravitationalForce.h"
#include "Simulation/Physics/LennardJones.h"
#include "Particles/Boundary.h"
#include "Particles/ReflectiveBoundary.h"


/* Logging */
#include "IO/Logger.h"
#include <IO/CLparser/CL.h>

/* Generators for Particles */
#include "Particles/ParticleGenerator.h"
#include "utils/CuboidGenerator.h"
#include "utils/SphereGenerator.h"



int main(int argc, char *argsv[]) {
    CL cl;
    std::unique_ptr<ParticleReader> reader;
    std::unique_ptr<ForceCalculation> forceCalculation;

    outputWriter::VTKWriter writer;
    SimParameters simParameters;
    int status = cl.parse_arguments(argc, argsv, simParameters);

    //any error in parsing
    if (status) {
        return 1;
    }

    std::string input_path = simParameters.getInputPath();

    if (simParameters.getInputMode() == "cuboid") {
        Logger::console->debug("Reading cuboid");
        reader = std::make_unique<CuboidReader>();
    }

    if (simParameters.getInputMode() == "particle") {
         Logger::console->debug("Reading particle");
        reader = std::make_unique<FileReader>();
    }

    if (simParameters.getInputMode() == "xml") {
        Logger::console->debug("Reading xml");
        reader = std::make_unique<XMLReader>();
    }

    if (!reader) {
        Logger::err_logger->error("Reader was not correctly initialized");
        exit(-1);
    }
    
    DirectSumContainer container_h;
    

    if (simParameters.getInputMode() == "xml") {
        reader->readFile(container_h, input_path, simParameters);
        
    }
    else {
        reader->readFile(container_h, input_path);
    }
    
    if (simParameters.getForce() == "lennard") {
        forceCalculation = std::make_unique<LennardJones>(simParameters.getEpsilon(), simParameters.getSigma());
        Logger::console->info("Force set to lennard");
    }
   
    if (simParameters.getForce() == "grav") {
        forceCalculation = std::make_unique<GravitationalForce>();
        Logger::console->info("Force set to grav");
    }

    ReflectiveBoundary boundary{simParameters.getBoxSize()[0], simParameters.getBoxSize()[1], simParameters.getBoxSize()[2], *forceCalculation, simParameters.getCutoffRadius(), simParameters.getSigma()};
    LinkedCellContainer container(boundary, simParameters.getCutoffRadius());
    container.addParticles(container_h.getParticleVector());
    Logger::console->info("Hello from MolSim for PSE!");
    Logger::console->info("Calculating ...");
   
    int iteration = 0;
    double current_time = simParameters.getStartTime();
 
    Simulation simulation(simParameters.getDeltaT(), container, *forceCalculation, simParameters.getAverageVelo(), boundary);
    // This is ugly and shouldn't be in main, but it is for a later refactor
    if (simParameters.isTesting()) {
        auto measure_start_time = std::chrono::high_resolution_clock::now();

        while (current_time < simParameters.getEndTime()) {
            simulation.runIteration();
            iteration++;
            current_time += simParameters.getDeltaT();
        }

        auto measure_end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(measure_end_time - measure_start_time);

        Logger::console->info("Time taken: {} milliseconds", duration.count());
    } else {
        // create directory
        writer.createMarkedDirectory();

        // for this loop, we assume: current x, current f and current v are known
        while (current_time < simParameters.getEndTime()) {
            simulation.runIterationReflective();

            iteration++;
            if (iteration % 10 == 0) {
                writer.plotParticles(simulation.getParticles(), simParameters.getBaseName(), iteration);
            }

            Logger::console->info("Iteration {} finished.", iteration);

            current_time += simParameters.getDeltaT();
        }

        Logger::console->info("Output written. Terminating...");
        return 0;
    }
}
