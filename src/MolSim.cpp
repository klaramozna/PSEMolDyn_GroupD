/* File IO */
#include "IO/input/FileReader.h"
#include "IO/input/CuboidReader.h"
#include "IO/input/ParticleReader.h"

#include "IO/output/outputWriter/XYZWriter.h"
#include "IO/output/outputWriter/VTKWriter.h"

#include "IO/input/SimParameters.h"
#include "IO/input/XMLReader.h"


/* Simulation Logic */
#include "Simulation/Simulation.h"
#include "Particles/LinkedCellContainer.h"
#include "Simulation/Physics/GravitationalForce.h"
#include "Simulation/Physics/LennardJones.h"
#include "Simulation/Physics/MixingRuleLennardJones.h"

#include "Particles/Boundary.h"

#include "Simulation/SimpleThermostat.h"
#include "Simulation/Physics/GravityForce.h"
#include "Simulation/Thermostat.h"
#include "Simulation/SimpleThermostat.h"
#include "Simulation/GradualThermostat.h"
#include "Simulation/FakeThermostat.h"
#include "Simulation/TempDifferenceThermostat.h"

/* Logging */
#include "IO/Logger.h"
#include <IO/CLparser/CL.h>

/* Checkpoint */
#include "IO/output/outputWriter/CheckpointWriter.h"
#include "IO/input/CheckpointReader.h"

/* Benchmark */
#include "Benchmark.h"



int main(int argc, char *argsv[]) {
    CL cl;
    std::unique_ptr<ParticleReader> reader;
    std::unique_ptr<ForceCalculation> forceCalculation;
    std::unique_ptr<Thermostat> thermostat;
    GravityForce gravity{0};


    outputWriter::VTKWriter writer;
    SimParameters simParameters;
    int status = cl.parse_input_path_and_mode_and_log(argc, argsv, simParameters);

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
        reader->readFile(container_h, input_path, simParameters);
    }
    else {
        reader->readFile(container_h, input_path);
    }

    status = cl.parse_arguments(argc, argsv, simParameters);
    if (status) {
        return 1;
    }

    if (simParameters.getForce() == "lennard") {
        forceCalculation = std::make_unique<LennardJones>(simParameters.getEpsilon(), simParameters.getSigma());
        Logger::console->info("Force set to lennard");
    }
   
    if (simParameters.getForce() == "grav") {
        forceCalculation = std::make_unique<GravitationalForce>();
        Logger::console->info("Force set to grav");
    }

    if (simParameters.getForce() == "MixingRuleLennardJones") {
        forceCalculation = std::make_unique<MixingRuleLennardJones>();
        Logger::console->info("Force set to Mixing Rule LennardJones");
    }

    if(simParameters.getThermostatType() == "none"){
        thermostat = std::make_unique<FakeThermostat>();
    }
    if(simParameters.getThermostatType() == "simple"){
        thermostat = std::make_unique<SimpleThermostat>(simParameters.getInitTemperature(), simParameters.getTargetTemperature(), simParameters.getThermostatCycleLength(), simParameters.getDim());
    }
    if(simParameters.getThermostatType() == "gradual"){
        thermostat = std::make_unique<GradualThermostat>(simParameters.getInitTemperature(), simParameters.getTargetTemperature(), simParameters.getThermostatCycleLength(), simParameters.getDim(), simParameters.getMaxTemperatureChange());
    }
    if(simParameters.getThermostatType() == "tempDiff"){
        thermostat = std::make_unique<TempDifferenceThermostat>(simParameters.getInitTemperature(), simParameters.getTargetTemperature(), simParameters.getThermostatCycleLength(), simParameters.getDim());
    }

    // Initializing boundary
    double particlesShift = 0;

    // Checking if container depth is too small
    if(simParameters.getDim() <= 2){
        simParameters.setBoxSize(std::array<double, 3>{simParameters.getBoxSize()[0], simParameters.getBoxSize()[1], 3 * simParameters.getCutoffRadius()});
        particlesShift = 3 * simParameters.getCutoffRadius() / 2;
    }

    Boundary boundary(simParameters.getBoxSize()[0], simParameters.getBoxSize()[1], simParameters.getBoxSize()[2],
             simParameters.getSigma(), simParameters.getBoundaryBehavior());

    if (boundary.getBoundaryTypes().empty()) {
        Logger::err_logger->error("Boundary was not correctly initialized");
        exit(-1);
    }

    if (simParameters.getGravityFactor() != 0.0) {
        gravity.setGravityFactor(simParameters.getGravityFactor());
        Logger::console->info("Gravity Force activated with factor {}", simParameters.getGravityFactor());
    }

    LinkedCellContainer container(boundary, simParameters.getCutoffRadius());

    /* To do: solve this dependency between readFile and container*/
    if(particlesShift != 0){
        container_h.applyToAll([&particlesShift](Particle& p){p.setX(p.getXVector() + VectorDouble3(std::array<double, 3>{0, 0, particlesShift}));});
    }

    container.addParticles(container_h.getParticleVector());


    /* read checkpoint if available and update container */
    if (!simParameters.getloadCheckpoint().empty()) {
        CheckpointReader cReader;
        std::string p = simParameters.getloadCheckpoint();
        cReader.readFile(container, p, simParameters);
    }
     
    Logger::console->info("Calculating ...");
    simParameters.print();
    int iteration = 0;
    double current_time = simParameters.getStartTime();

    Simulation simulation(simParameters.getDeltaT(), simParameters.getSigma(),  container, *forceCalculation, *thermostat, simParameters.getAverageVelo(), boundary, gravity, simParameters.getBrownianMotion(), simParameters.getDim());

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
       
        writer.createMarkedDirectory();
        int total_iterations = static_cast<int>(simParameters.getEndTime() / simParameters.getDeltaT());
        int percentage=0;
        int old_percentage=0;

    Logger::console->info("Progress: {}%", percentage);
     // for this loop, we assume: current x, current f and current v are known
    while (current_time < simParameters.getEndTime()) {
        simulation.runIteration();

        iteration++;
        if (iteration % simParameters.getWriteFrequency() == 0) {
            writer.plotParticles(simulation.getParticles(), simParameters.getBaseName(), iteration);
        }

        current_time += simParameters.getDeltaT();

        percentage = static_cast<int>((static_cast<double>(iteration) / total_iterations) * 100);

        if (percentage % 10 == 0 && percentage > old_percentage && percentage != 0 && percentage <= 100) {
            Logger::console->info("Progress: {}%", percentage);
            old_percentage = percentage;
        }
    }

        /* store checkpoint if specified */
        if (!simParameters.getStoreCheckpoint().empty()) {
            CheckpointWriter c;
            Logger::console->info("Storing checkpoint ...");
            c.writeCheckpoint(container, simParameters.getStoreCheckpoint());
        }
        
        Logger::console->info("Output written with frequency {}. Terminating...", simParameters.getWriteFrequency());
        return 0;
    }
}
