/*
 * Simulation.cpp
 *
 *  Created on: 01.11.2023
 *      Author: rodrigoflx
 */

#include <cmath>
#include <iostream>
#include "Simulation.h"

#include "Particles/LinkedCellContainer.h"
#include "Particles/BoundaryEnforcer.h"
#include "Simulation/FakeThermostat.h"
#include "IO/Logger.h"

std::array<double, 3> maxwellBoltzmannDistributedVelocity(double averageVelocity, size_t dimensions);

Simulation::Simulation(SimParameters& simParameters, LinkedCellContainer& container, ForceCalculation &calculation, Thermostat& thermostat, Boundary &boundary, GravityForce &gravity, HardcodedPullForce &hardcodedPullForce) :
                        container(container),
                        forceCalculation(calculation),
                        thermostat(thermostat),
                        boundaryEnforcer(simParameters.getSigma(), container, boundary.getDimensions(), boundary.getBoundaryTypes(), forceCalculation),
                        gravity(gravity),
                        pullForce(hardcodedPullForce),
                        simParameters(simParameters) {
    // Apply brownian motion
    if(simParameters.getBrownianMotion()){
        if(typeid(thermostat) == typeid(FakeThermostat())) {
            double averageVelo = simParameters.getAverageVelo();
            double dim = simParameters.getDim();
            container.applyToAll([&averageVelo, &dim](Particle &p) {
                VectorDouble3 velocity = VectorDouble3(maxwellBoltzmannDistributedVelocity(averageVelo, dim));
                p.setV(p.getVVector() + velocity);
            });
        }
        else{
            container.applyToAll([&thermostat](Particle &p) {
                thermostat.initializeBrownianMotion(p);
            });
        }
    }
}


Simulation::~Simulation() = default;

std::vector<Particle> Simulation::getParticles() {
    return container.getParticleVector();
}


void Simulation::calculateF(Particle& p1, Particle& p2) {
    VectorDouble3 result = this->forceCalculation.CalculateForces(p1,p2);
    if (!std::isnan(result.at(0)) && !std::isnan(result.at(1)) && !std::isnan(result.at(2))) {
        p1.setF(p1.getFVector() + result);
        p2.setF(p2.getFVector() - result);
    }
}

void Simulation::calculateV(Particle& p) const {
    VectorDouble3 v_i = p.getVVector() + (simParameters.getDeltaT()/ (2. * p.getM()) * (p.getOldFVector() + p.getFVector()));
    p.setV(v_i);
}

void Simulation::calculateX(Particle& p) const {
    VectorDouble3 x_i = p.getXVector() + simParameters.getDeltaT() * p.getVVector()
            + ((simParameters.getDeltaT() * simParameters.getDeltaT()) / (2. * p.getM())) * p.getOldFVector();
    p.setX(x_i);
}

void Simulation::applyGravity(Particle& p) {
    VectorDouble3 result = gravity.CalculateForce(p);
    p.setF(p.getFVector() + result);
}

void Simulation::applyPullForce(Particle& p) {
    if (p.getHardcodeFlag() == true){
        VectorDouble3 result = pullForce.CalculateForce(p);
        p.setF(p.getFVector() + result);
    }
}


void Simulation::runIteration() {
    // calculate new x
    container.applyToAll([this](Particle& p) { calculateX(p); });

    // calculate new f
    container.applyToAll([](Particle& p) { setOldForce(p); });

    // apply boundary conditions
    container.applyToBoundary([this](Particle& p) { boundaryEnforcer.applyBoundaryConditionsForParticle(p); });

    container.applyToPairs([this](Particle& p1, Particle& p2) { calculateF(p1, p2); });

    container.deleteHaloParticles();

    container.applyToAll([this](Particle& p) { applyGravity(p); });

    if (simParameters.isMembrane()) {
        if (getCurrentTime() < simParameters.getHardcodedForceEndTime()) {
            container.applyToAll([this](Particle& p) { applyPullForce(p); });
        }
         container.applyToAll([this](Particle& p) { applyHarmonicForces(p); });
    }
    // calculate new v
    container.applyToAll([this](Particle& p) { calculateV(p); });

    // adjust temperature
    thermostat.updateState(container.getParticleVector());
    container.applyToAll([this](Particle& p){thermostat.updateTemperature(p);});
    thermostat.updateIteration();
}

void Simulation::setOldForce(Particle& p) {
    p.setOldF((p.getFVector()));
    p.setF(VectorDouble3());
}

void Simulation::applyHarmonicForces(Particle& p) {

        double stiffness = p.getStiffness();
        double averageBondLength = p.getBondLength();

        for (auto neighb : p.getParallelNeighbours())
        {
                double distance = (p.getXVector() - neighb.get()->getXVector()).getL2Norm();
                auto result = (stiffness * (distance - averageBondLength) / distance) * (neighb.get()->getXVector() - p.getXVector());
                if (!std::isnan(result.at(0)) && !std::isnan(result.at(1)) && !std::isnan(result.at(2))){
                    p.setF(p.getFVector() + result);
                }           
        }

        double square_root_of_two = std::sqrt(2);

        for (auto neighb : p.getDiagonalNeighbours())
        {
                double distance = (p.getXVector() - neighb.get()->getXVector()).getL2Norm();
                auto result = (stiffness * (distance - square_root_of_two * averageBondLength) / distance) * (neighb.get()->getXVector() - p.getXVector());
                if (!std::isnan(result.at(0)) && !std::isnan(result.at(1)) && !std::isnan(result.at(2))){
                    p.setF(p.getFVector() + result);
                }
        }

}

void Simulation::runSimulation() {
    int iteration = 0;
    current_time = simParameters.getStartTime();

     if (simParameters.isTesting()) {

        Benchmark benchmark;
        benchmark.startBenchmark();

        while (current_time < simParameters.getEndTime()) {
            runIteration();
            iteration++;
            current_time += simParameters.getDeltaT();
        }

        benchmark.stopBenchmark();
        int number_of_iterations = simParameters.getEndTime() / simParameters.getDeltaT();
        benchmark.printBenchmarkResults(benchmark.getElapsedTimeInSeconds(), number_of_iterations ,container.getSize());

    } else {
        outputWriter::VTKWriter writer;
        writer.createMarkedDirectory();
        int total_iterations = static_cast<int>(simParameters.getEndTime() / simParameters.getDeltaT());
        int percentage=0;
        int old_percentage=0;

    Logger::console->info("Progress: {}%", percentage);
     // for this loop, we assume: current x, current f and current v are known
    while (current_time < simParameters.getEndTime()) {
        runIteration();

        iteration++;
        if (iteration % simParameters.getWriteFrequency() == 0) {
            writer.plotParticles(getParticles(), simParameters.getBaseName(), iteration);
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
    }


}

