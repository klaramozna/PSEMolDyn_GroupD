/*
 * XMLReader.cpp
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#include "XMLReader.h"
#include "simulationFormat.h"
#include "./../Logger.h"
#include "./../../Simulation/Simulation.h"
#include "./../../Simulation/Physics/LennardJones.h"
#include "./../../utils/CuboidGenerator.h"
#include "./../../utils/SphereGenerator.h"
#include <iostream>

XMLReader::XMLReader() = default;

XMLReader::~XMLReader() = default;

void XMLReader::readFile(const std::shared_ptr<ParticleContainer> &container, std::string &filename, SimParameters& SimParameters) {
    try {
        std::unique_ptr<Simulation_t> sim(Simulation(filename));

        if (sim->log_level().present()) {
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
                Logger::console->debug("Reading force type 1 from XML");
                lennardJones_t& lennard = *(sim->force()->lennard());
                double epsilon = lennard.Epsilon();
                double sigma = lennard.Sigma();
                Logger::console->debug("Reading Sigma {} and Epsilon {} from XML", epsilon, sigma);
                SimParameters.setForce("lennard");
                SimParameters.setEpsilon(epsilon);
                SimParameters.setSigma(sigma);
            } else if (sim->force()->grav()) {
                Logger::console->debug("Reading force type 2 from XML");
                 SimParameters.setForce("grav");

            }
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
            std::array<double, 3> velocity = {cuboid.initial_velocity().x(), cuboid.initial_velocity().y(), cuboid.initial_velocity().z()};
            CuboidGenerator generator {lowerLeftCoord, n1, n2, n3, distance, mass, velocity};

            std::vector<Particle> readContainer = generator.generateParticles(i);
            container->addParticles(readContainer);
            i++;
    }

         i = 0;
        for (const auto& sphere: sim->sphere()) {
            Logger::console->debug("Reading Sphere number {} from XML", i);
            std::array<double,3> center = {sphere.center().x(), sphere.center().y(), sphere.center().z()};
            int radius = sphere.radius();
            double distance = sphere.distance();
            double mass = sphere.mass();
            std::array<double, 3> velocity = {sphere.initial_velocity().x(), sphere.initial_velocity().y(), sphere.initial_velocity().z()};
            SphereGenerator generator {center, distance, radius, mass, velocity};
            std::vector<Particle> particles = generator.generateParticles(i);
            container->addParticles(particles);
            i++;
    }



    }
    catch (const xml_schema::exception& e) {
        Logger::err_logger->error("{}",e.what());

    }

}