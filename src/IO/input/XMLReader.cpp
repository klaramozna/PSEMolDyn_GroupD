/*
 * XMLReader.cpp
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#include "XMLReader.h"
#include "../xsdCode/simulationFormat.h"
#include "./../Logger.h"
#include "./../../Simulation/Simulation.h"
#include "./../../utils/CuboidGenerator.h"
#include "./../../utils/SphereGenerator.h"

XMLReader::XMLReader() = default;

XMLReader::~XMLReader() = default;

void XMLReader::readFile(ParticleContainer &container, std::string &filename, SimParameters& SimParameters) {
    try {
        std::unique_ptr<Simulation_t> sim(Simulation(filename));

        if (sim->log_level().present() && !Logger::is_log_level_set()) {
            SimParameters.setLogLevel(sim->log_level().get());
            Logger::init(sim->log_level().get());
        }

        SimParameters.setDeltaT(sim->delta_t().get());
        SimParameters.setEndTime(sim->t_end().get());

        if (sim->base_name().present()){
            Logger::console->debug("Reading Base name {} from XML", sim->base_name().get());
            SimParameters.setBaseName(sim->base_name().get());
        }

        if (sim->writeFrequency().present()){
            Logger::console->debug("Reading Writing Frequency {} from XML", sim->writeFrequency().get());
            SimParameters.setWriteFrequency(sim->writeFrequency().get());
        }


        if (sim->testing_mode().present()) {
            Logger::console->debug("Reading testing mode {} from XML", sim->testing_mode().get());
            SimParameters.setTesting(sim->testing_mode().get());
        }

        if (sim->averageVelo().present()) {
            Logger::console->debug("Reading average Velo {} from XML", sim->averageVelo().get());
            SimParameters.setAverageVelo(sim->averageVelo().get());
        }

        if (sim->force()) {
            if (sim->force()->lennard()) {
                Logger::console->debug("Reading force type 1 (lennard jones) from XML");
                lennardJones_t& lennard = *(sim->force()->lennard());
                double epsilon = lennard.Epsilon();
                double sigma = lennard.Sigma();
                Logger::console->debug("Reading Sigma {} and Epsilon {} from XML", epsilon, sigma);
                SimParameters.setForce("lennard");
                SimParameters.setEpsilon(epsilon);
                SimParameters.setSigma(sigma);
            } else if (sim->force()->grav()) {
                Logger::console->debug("Reading force type 2 (gravitational) from XML");
                SimParameters.setForce("grav");
            }
            else if (sim->force()->MixingRuleLennardJones()) {
                Logger::console->debug("Reading force type 3 (Mixing Rule Lennard Jones) from XML");
                SimParameters.setForce("MixingRuleLennardJones");
            } 
        }

        if (sim->thermostat()) {
            if (sim->thermostat()->none()) {
                Logger::console->debug("Reading thermostat type 1 (none) from XML");
                SimParameters.setThermostatType("none");
            } else if (sim->thermostat()->simple()) {
                simpleThermostatType& thermostat = *(sim->thermostat()->simple());
                Logger::console->debug("Reading thermostat type 2 (simple) from XML");
                SimParameters.setThermostatType("simple");
                SimParameters.setInitTemperature(thermostat.initTemperature());
                SimParameters.setThermostatCycleLength(thermostat.thermostatCycleLength());
                SimParameters.setTargetTemperature(thermostat.targetTemperature());
            }
            else if (sim->thermostat()->gradual()) {
                gradualThermostatType& thermostat = *(sim->thermostat()->gradual());
                Logger::console->debug("Reading thermostat type 3 (gradual) from XML");
                SimParameters.setThermostatType("gradual");
                SimParameters.setInitTemperature(thermostat.initTemperature());
                SimParameters.setThermostatCycleLength(thermostat.thermostatCycleLength());
                SimParameters.setTargetTemperature(thermostat.targetTemperature());
                SimParameters.setMaxTemperatureChange(thermostat.maxTemperatureChange());
            }
        }

        if (sim->gravity().present()) {
                Logger::console->debug("Reading Gravity froce from XML");
                double gravity_factor = (sim->gravity()->gravity_factor());
                Logger::console->debug("Reading gravity factor {} from XML", gravity_factor);
                SimParameters.setGravityFactor(gravity_factor);
        }

        int i = 0;
        for (const auto& cuboid : sim->cuboid()) {
            Logger::console->debug("Reading Cuboid number {} from XML", i);
            std::array<double,3> lowerLeftCoord = {cuboid.lower_left_coord().x(), cuboid.lower_left_coord().y(), cuboid.lower_left_coord().z()};
            int n1 = cuboid.number_of_particles().x();
            int n2 = cuboid.number_of_particles().y();
            int n3 = cuboid.number_of_particles().z();
            double distance = cuboid.distance();
            double mass = cuboid.mass();
            double epsilon = cuboid.epsilon_cuboid_default_value();
            double sigma = cuboid.sigma_cuboid_default_value();
            if (cuboid.epsilon_cuboid().present()){
                epsilon = cuboid.epsilon_cuboid().get();
            }
            if (cuboid.sigma_cuboid().present()) {
                sigma = cuboid.sigma_cuboid().get();
            }
            std::array<double, 3> velocity = {cuboid.initial_velocity().x(), cuboid.initial_velocity().y(), cuboid.initial_velocity().z()};
            CuboidGenerator generator {lowerLeftCoord, n1, n2, n3, distance, mass, velocity, epsilon, sigma};
            std::vector<Particle> particles = generator.generateParticles(i);
            container.addParticles(particles);
            i++;
        }

        i = 0;
        for (const auto& sphere: sim->sphere()) {
            Logger::console->debug("Reading Sphere number {} from XML", i);
            std::array<double,3> center = {sphere.center().x(), sphere.center().y(), sphere.center().z()};
            int radius = sphere.radius();
            double distance = sphere.distance();
            double mass = sphere.mass();
            double epsilon = sphere.epsilon_sphere_default_value();
            double sigma = sphere.sigma_sphere_default_value();
            if (sphere.epsilon_sphere().present()){
                epsilon = sphere.epsilon_sphere().get();
            }
            if (sphere.sigma_sphere().present()) {
                sigma = sphere.sigma_sphere().get();
            }
            std::array<double, 3> velocity = {sphere.initial_velocity().x(), sphere.initial_velocity().y(), sphere.initial_velocity().z()};
            SphereGenerator generator {center, distance, radius, mass, velocity, epsilon, sigma};
            std::vector<Particle> particles;
            if (sphere.dimension() == "3D"){
                particles = generator.generateParticles(i);
            }
            else {
                particles = generator.generateDisk(i);
            }
            container.addParticles(particles);
            i++;
        }
        if (sim->boundaries()) {
            std::array <double,3> boxSize {sim->boundaries()->BoxSize().x(), sim->boundaries()->BoxSize().y(), sim->boundaries()->BoxSize().z()};
            SimParameters.setBoxSize(boxSize);
            SimParameters.setDimension(SimParameters.getBoxSize()[2] == 0? 2 : 3);
            std::array<std::string, 6> bound_beh {sim->boundaries()->Front(),
                                                  sim->boundaries()->Back(),
                                                  sim->boundaries()->Top(),
                                                  sim->boundaries()->Right(),
                                                  sim->boundaries()->Bottom(),
                                                  sim->boundaries()->Left() };
            SimParameters.setBoundaryBehavior(bound_beh);

            Logger::console->debug("Box Size Content:");
            for (const auto& size : boxSize) {
                Logger::console->debug("Size: {}", size);
            }

            Logger::console->debug("Boundary Behavior Content:");
            for (const auto& behavior : bound_beh) {
                Logger::console->debug("Behavior: {}", behavior);
            }
        }

        if (sim->cutoffRadius().present()){
            Logger::console->debug("Reading cut off Radius {} from XML", sim->cutoffRadius().get());
            SimParameters.setCutoffRadius(sim->cutoffRadius().get());
        }

        if (sim->parallelization_spec_xml().present()){
            std::array<int, 3> subdomain;
            ParallelizationType type;
            SchedulerType schedulerType;
            long num_threads = sim->parallelization_spec_xml()->numThreads().get();

            if (sim->parallelization_spec_xml()->type().present()) {
                if (sim->parallelization_spec_xml()->type().get() == "subdomain" && !sim->parallelization_spec_xml()->subDomain().present()) {
                    Logger::err_logger->error("Subdomain type requires subdomain to be specified");
                    exit(-1);
                }
            }

            if (sim->parallelization_spec_xml()->subDomain().present()) {
                subdomain = {
                        static_cast<int>(sim->parallelization_spec_xml()->subDomain().get().x()),
                        static_cast<int>(sim->parallelization_spec_xml()->subDomain().get().y()),
                        static_cast<int>(sim->parallelization_spec_xml()->subDomain().get().z())
                };
                Logger::console->debug("Reading subdomain [{}, {}, {}] from XML", subdomain[0], subdomain[1], subdomain[2]);
            }

            Logger::console->debug("Reading parallelization strategy type {} from XML", sim->parallelization_spec_xml()->type().get());

            try {
                type = ParallelizationSpec::getParallelizationTypeFromStr(sim->parallelization_spec_xml()->type().get());
            } catch (const std::invalid_argument& e) {
                Logger::err_logger->error("{}",e.what());
                exit(-1);
            }

            try {
                Logger::console->debug("Reading scheduling type {} from XML", sim->parallelization_spec_xml()->schedule().get());
                schedulerType = ParallelizationSpec::getSchedulerTypeFromStr(sim->parallelization_spec_xml()->schedule().get());
            } catch (const std::invalid_argument& e) {
                Logger::err_logger->error("{}",e.what());
                exit(-1);
            }

            Logger::console->debug("Reading number of threads({}) from XML", sim->parallelization_spec_xml().get().numThreads().get());

            SimParameters.getParallelizationSpec().setType(type);
            SimParameters.setSchedulerType(schedulerType);
            SimParameters.getParallelizationSpec().setChunksize(sim->parallelization_spec_xml()->chunksize().get());
            SimParameters.getParallelizationSpec().setNumThreads(sim->parallelization_spec_xml()->numThreads().get());

        }

        Logger::console->debug("Reading brownian motion indicator {} from XML", sim->brownian_motion());
        SimParameters.setBrownianMotion(sim->brownian_motion());



    }
    catch (const xml_schema::exception& e) {
        Logger::err_logger->error("{}",e.what());
    }
}