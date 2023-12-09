//
// Created by RayenManai on 08.12.23.
//

#include "CheckpointWriter.h"
#include "../../Logger.h"
#include <fstream>


    CheckpointWriter::CheckpointWriter(){

       Logger::console->debug("CheckpointWriter initialised");
    
    }

    CheckpointWriter::~CheckpointWriter(){

       Logger::console->debug("CheckpointWriter destructed");
    
    }


    void CheckpointWriter::writeCheckpoint (ParticleContainer &container, std::string filename){
        
        Checkpoint_t checkpoint;
        Checkpoint_t::particle_sequence &particle_sequence = checkpoint.particle();


        for (auto p : container.getParticleVector()){
            
        particle_t particle(
            commonSchema::double_3d(p.getX().at(0), p.getX().at(1), p.getX().at(2)),
            commonSchema::double_3d(p.getVVector().at(0), p.getVVector().at(1), p.getVVector().at(2)),
            commonSchema::double_3d(p.getFVector().at(0), p.getFVector().at(1), p.getFVector().at(2)),
            commonSchema::double_3d(p.getOldFVector().at(0), p.getOldFVector().at(1), p.getOldFVector().at(2)),
            p.getM(),
            p.getType()
        );

        // Add the particle to the sequence
        particle_sequence.push_back(particle);

        }

        xml_schema::namespace_infomap map;
        map[""].schema = "../../../../input/checkpointFormat.xsd";    
        std::ofstream ofs (filename);
        Checkpoint(ofs, checkpoint, map);
    }

   
