//
// Created by RayenManai on 04.01.24.
//

#include "MembraneGenerator.h"
#include <stdexcept>

MembraneGenerator::MembraneGenerator(std::array<double, 3> corner, int n1, int n2, int n3, double particleDistance,
                                 double mass, std::array<double, 3> velocity, double epsilon, double sigma, double stiffness, double bond_length, std::vector<std::array <int,3>> indices): corner(), velocity() {
    if((n1 <= 0) | (n2 <= 0) | (n3 <= 0)){
        throw std::invalid_argument("The number of particles in a dimension has to be strictly positive.");
    }
    this->corner = corner;
    this->n1= n1;
    this->n2 = n2;
    this->n3 = n3;
    this->particleDistance = particleDistance;
    this->mass = mass;
    this->velocity = velocity;
    particles.reserve(n1 * n2 * n3);
    this->epsilon = epsilon;
    this->sigma = sigma;
    this->stiffness = stiffness;
    this->bond_length = bond_length;
    this->indices = indices;
}

std::vector<std::shared_ptr<Particle>> MembraneGenerator::generateParticles(int type) {
    int id = 0;
    bool hardcode_flag = false;
    double xCorner = corner[0];
    double yCorner = corner[1];
    double zCorner = corner[2];
    for(int x = 0; x < n1; x++){
        for(int y = 0; y < n2; y++){
            for(int z = 0; z < n3; z++){
                std::array<double, 3> particlePosition{xCorner + particleDistance * x, yCorner + particleDistance * y, zCorner + particleDistance * z};
                if (isHardcoded(x, y, z, indices)){
                    hardcode_flag = true;
                    std::shared_ptr<Particle> particlePtr = std::make_shared<Particle>(particlePosition, velocity, mass, epsilon, sigma, stiffness, bond_length, std::vector<std::shared_ptr<Particle>> {}, std::vector<std::shared_ptr<Particle>> {}, id, hardcode_flag, 1);
                    particles.emplace_back(particlePtr);
                    hardcode_flag = false;
                }
                else {
                    std::shared_ptr<Particle> particlePtr = std::make_shared<Particle>(particlePosition, velocity, mass, epsilon, sigma, stiffness, bond_length, std::vector<std::shared_ptr<Particle>> {}, std::vector<std::shared_ptr<Particle>> {}, id, hardcode_flag, type);
                    particles.emplace_back(particlePtr);
                }
                id ++;
            }
        }
    }

    int index = 0;
            for (int x = 0; x < n1; x++)
            {
                for (int y = 0; y < n2; y++)
                {
                    particles.at(index).get()->setParallelNeighbours(calculateParallelNeighbourIndices(n1, n2, n3, index));
                    particles.at(index).get()->setDiagonalNeighbours(calculateDiagonalNeighbourIndices(n1, n2, n3, index));
                    index++;
                }
            }

    return particles;
}

std::vector<std::shared_ptr<Particle>> MembraneGenerator::calculateParallelNeighbourIndices (int n1, int n2, int n3, int index) {
    std::vector<std::shared_ptr<Particle>> result;
    
    int maxIndex = n1 * n2 -1;
    // check not top
    if (index + 1 <= maxIndex && (index + 1)% n2 != 0){
        result.emplace_back(particles.at(index + 1));
    }
    //check not bottom
    if (index - 1 >= 0 && index % n2 != 0){
        result.emplace_back(particles.at(index - 1));
    }

    if (index + n2 <= maxIndex){
        result.emplace_back(particles.at(index + n2));
    }

    if (index -n2 >= 0 ){
        result.emplace_back(particles.at(index - n2));
    }
    return result;
}


std::vector<std::shared_ptr<Particle>> MembraneGenerator::calculateDiagonalNeighbourIndices (int n1, int n2, int n3, int index) {
    std::vector<std::shared_ptr<Particle>>result;
    
    int maxIndex = n1 * n2 -1;
    //check not top
    if (index + n2 + 1 <= maxIndex && (index + 1)% n2 != 0){
        result.emplace_back(particles.at(index + n2 + 1));
    }
    //check not bottom 
    if (index -n2 - 1 >= 0 && index % n2 != 0 ){
        result.emplace_back(particles.at(index - n2 - 1));
    }
    //check not bottom
    if (index + n2 - 1 <= maxIndex && index % n2 != 0){
        result.emplace_back(particles.at(index + n2 - 1));
    }
    // check not top
    if (index -n2 + 1>= 0 && (index + 1)% n2 != 0){
        result.emplace_back(particles.at(index - n2 + 1));
    }
    return result;
}

bool MembraneGenerator::isHardcoded(int x, int y, int z, std::vector<std::array<int,3>> indices){
    //loop through the arrays in indices and return true only when indice = [x, y, z]
    for (const auto& indice : indices) {
        if (indice[0] == x && indice[1] == y && indice[2] == z) {
            return true;
        }
    }
    return false;
}
