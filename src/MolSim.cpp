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
#include "Simulation/Physics/TruncatedLennardJones.h"

#include "Particles/Boundary.h"

#include "Simulation/SimpleThermostat.h"
#include "Simulation/Physics/GravityForce.h"
#include "Simulation/Physics/HardcodedPullForce.h"
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





int main(int argc, char *argsv[]) {
    CL cl;
    std::unique_ptr<ParticleReader> reader;
    XMLReader xmlReader {};
    std::unique_ptr<ForceCalculation> forceCalculation;
    std::unique_ptr<Thermostat> thermostat;
    GravityForce gravity{std::array<double,3>{0,0,0}};
    HardcodedPullForce pullForce{std::array<double,3>{0,0,0}};

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

    DirectSumContainer container_h;

    if (simParameters.getInputMode() == "xml") {
        Logger::console->debug("Reading xml");
        xmlReader.readFile(input_path, simParameters);
    }
    else {
        reader->readFile(input_path, simParameters);
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

    if (simParameters.getForce() == "TruncatedLennardJones") {
        forceCalculation = std::make_unique<TruncatedLennardJones>();
        Logger::console->info("Force set to Truncated LennardJones");
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

    if (simParameters.getGravityFactor() != std::array<double,3>{0, 0, 0}) {
        gravity.setGravityFactor(simParameters.getGravityFactor());
        Logger::console->info("Gravity Force activated with factors x, y ,z: {} {} {}", simParameters.getGravityFactor().at(0), simParameters.getGravityFactor().at(1), simParameters.getGravityFactor().at(2));
    }
    if (simParameters.getHardcodedPullFactors() != std::array<double,3>{0, 0, 0}) {
        pullForce.setPullFactors(simParameters.getGravityFactor());
        Logger::console->info("Pull Force activated with factors x, y ,z: {} {} {}", simParameters.getHardcodedPullFactors().at(0), simParameters.getHardcodedPullFactors().at(1), simParameters.getHardcodedPullFactors().at(2));
    }

    LinkedCellContainer container(boundary, simParameters.getCutoffRadius());

    container.addParticlesPointer(xmlReader.getParticles());

    if(particlesShift != 0){
        container.applyToAll([&particlesShift](Particle& p){p.setX(p.getXVector() + VectorDouble3(std::array<double, 3>{0, 0, particlesShift}));});
    }


    /* read checkpoint if available and update container */
    if (!simParameters.getloadCheckpoint().empty()) {
        CheckpointReader cReader;
        std::string p = simParameters.getloadCheckpoint();
        cReader.readFile(p, simParameters);
        container.addParticlesPointer(cReader.getParticles());
    }
     
    Logger::console->info("Calculating ...");
    simParameters.print();
    int iteration = 0;
    double current_time = simParameters.getStartTime();

    Simulation simulation(simParameters, container, *forceCalculation, *thermostat, boundary, gravity, pullForce);

    Logger::console->info("Number of particles before: {}", container.getParticleVector().size());
    simulation.runSimulation();
    Logger::console->info("Number of particles after: {}", container.getParticleVector().size());
    
    return 0;
   
}
