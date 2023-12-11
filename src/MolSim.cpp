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
#include "Simulation/SimpleThermostat.h"

/* Logging */
#include "IO/Logger.h"
#include <IO/CLparser/CL.h>

/* Generators for Particles */
#include "Particles/ParticleGenerator.h"
#include "utils/CuboidGenerator.h"
#include "utils/SphereGenerator.h"

/* Checkpoint */
#include "IO/output/outputWriter/CheckpointWriter.h"
#include "IO/input/CheckpointReader.h"

/* Benchmark */
#include "Benchmark.h"



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

    /* To do: solve this dependency between readFile and container*/
    DirectSumContainer container_h;

    if (simParameters.getInputMode() == "xml") {
        reader->readFile(container, input_path, simParameters);
    }
    else {
        reader->readFile(container, input_path);
    }
    
    Logger::console->info("Hello from MolSim for PSE!");

    if (simParameters.getForce() == "lennard") {
        forceCalculation = std::make_unique<LennardJones>(simParameters.getEpsilon(), simParameters.getSigma());
        Logger::console->info("Force set to lennard");
    }
   
    if (simParameters.getForce() == "grav") {
        forceCalculation = std::make_unique<GravitationalForce>();
        Logger::console->info("Force set to grav");
    }

    Boundary boundary{simParameters.getBoxSize()[0], simParameters.getBoxSize()[1], simParameters.getBoxSize()[2], *forceCalculation, simParameters.getCutoffRadius()};
    LinkedCellContainer container(boundary, simParameters.getCutoffRadius());

    /* To do: solve this dependency between readFile and container*/
    container.addParticles(container_h.getParticleVector());


    /* read checkpoint if available and update container */
    if (!simParameters.getloadCheckpoint().empty()) {
        CheckpointReader cReader;
        std::string p = simParameters.getloadCheckpoint();
        cReader.readFile(container, p, simParameters);
    }
     
    Logger::console->info("Calculating ...");
   
    int iteration = 0;
    double current_time = simParameters.getStartTime();


    //TODO: change once xml parameters adjusted
    SimpleThermostat thermostat{20, 20, 50, 3};


    Simulation simulation(simParameters.getDeltaT(), container, *forceCalculation, thermostat, simParameters.getAverageVelo(), boundary);
  
    // This is ugly and shouldn't be in main, but it is for a later refactor
    if (simParameters.isTesting()) {

        Benchmark benchmark;
        benchmark.startBenchmark();

        while (current_time < simParameters.getEndTime()) {
            simulation.runIteration();
            iteration++;
            current_time += simParameters.getDeltaT();
        }

        benchmark.stopBenchmark();
        int number_of_iterations = simParameters.getEndTime() / simParameters.getDeltaT();
        benchmark.printBenchmarkResults(benchmark.getElapsedTimeInSeconds(), number_of_iterations ,container.getSize());

    } else {
        // for this loop, we assume: current x, current f and current v are known
        while (current_time < simParameters.getEndTime()) {
            simulation.runIteration();

            iteration++;
            if (iteration % 10 == 0) {
                writer.plotParticles(simulation.getParticles(), simParameters.getBaseName(), iteration);
            }

            Logger::console->info("Iteration {} finished.", iteration);

            current_time += simParameters.getDeltaT();
        }

        /* store checkpoint if specified */
        if (!simParameters.getStoreCheckpoint().empty()) {
            CheckpointWriter c;
            Logger::console->info("Storing checkpoint ...");
            c.writeCheckpoint(container, simParameters.getStoreCheckpoint());
        }
        
        Logger::console->info("Output written. Terminating...");
        return 0;
    }
}
