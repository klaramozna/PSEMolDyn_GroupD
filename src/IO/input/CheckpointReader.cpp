/*
 * CheckpointReader.cpp
 *
 *  Created on: 11.12.2023
 *      Author: RayenManai
 */

#include "CheckpointReader.h"
#include "../xsdCode/checkpointFormat.h"
#include "./../Logger.h"
#include <iostream>

CheckpointReader::CheckpointReader() = default;

CheckpointReader::~CheckpointReader() = default;

void CheckpointReader::readFile (std::string &filename, SimParameters& simParameters) {
    /* Reading from checkpoints */
    try {  
        
        Logger::console->debug("Reading checkpoint");
        std::unique_ptr<Checkpoint_t> c(Checkpoint(filename));
        int i = 0;
        for (const auto& p : c->particle()) {

            Particle particle_from_xml (
            std::array<double,3>{p.x().x(), p.x().y(), p.x().z()},
            std::array<double,3>{p.v().x(), p.v().y(), p.v().z()},
            p.m(),
            p.epsilon(),
            p.sigma(),
            p.type()           
            );
            particle_from_xml.setOldF(p.old_f().x(), p.old_f().y(), p.old_f().z());
            particle_from_xml.setF(p.f().x(), p.f().y(), p.f().z());
            std::shared_ptr<Particle> particlePtr = std::make_shared<Particle>(particle_from_xml);
            particles.emplace_back(particlePtr);
            i++;

    }

    Logger::console->debug("Read {} stored particles from the checkpoint", i);
        
    }
    catch (const xml_schema::exception& e) {
        Logger::err_logger->error("{}",e.what());
    }
}