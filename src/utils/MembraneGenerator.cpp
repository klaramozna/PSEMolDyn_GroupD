//
// Created by RayenManai on 04.01.24.
//

#include "MembraneGenerator.h"
#include <stdexcept>

MembraneGenerator::MembraneGenerator(std::array<double, 3> corner, int n1, int n2, int n3, double particleDistance,
                                 double mass, std::array<double, 3> velocity, double epsilon, double sigma, double stiffness, double bond_length): corner(), velocity() {
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
}

std::vector<Particle> MembraneGenerator::generateParticles(int type) {
    int id = 0;
    double xCorner = corner[0];
    double yCorner = corner[1];
    double zCorner = corner[2];
    for(int x = 0; x < n1; x++){
        for(int y = 0; y < n2; y++){
            for(int z = 0; z < n3; z++){
                std::array<double, 3> particlePosition{xCorner + particleDistance * x, yCorner + particleDistance * y, zCorner + particleDistance * z};
                particles.emplace_back(particlePosition, velocity, mass, epsilon, sigma, stiffness, bond_length, std::vector<int>{}, std::vector<int>{}, id, type);
                id ++;
            }
        }
    }

    int index = 0;
            for (int x = 0; x < n1; x++)
            {
                for (int y = 0; y < n2; y++)
                {
                    particles.at(index).setParallelNeighbours(calculateParallelNeighbourIndices(n1, n2, n3, index));
                    particles.at(index).setDiagonalNeighbours(calculateDiagonalNeighbourIndices(n1, n2, n3, index));
                    index++;
                }
            }

    return particles;
}

std::vector<int> MembraneGenerator::calculateParallelNeighbourIndices (int n1, int n2, int n3, int index) {
    std::vector<int> result;
    
    int maxIndex = n1 * n2 -1;
    // check not top
    if (index + 1 <= maxIndex && (index + 1)% n2 != 0){
        result.emplace_back(index + 1);
    }
    //check not bottom
    if (index - 1 >= 0 && index % n2 != 0){
        result.emplace_back(index - 1);
    }

    if (index + n2 <= maxIndex){
        result.emplace_back(index + n2);
    }

    if (index -n2 >= 0 ){
        result.emplace_back(index - n2);
    }
    return result;
}


std::vector<int> MembraneGenerator::calculateDiagonalNeighbourIndices (int n1, int n2, int n3, int index) {
    std::vector<int> result;
    
    int maxIndex = n1 * n2 -1;
    //check not top
    if (index + n2 + 1 <= maxIndex && (index + 1)% n2 != 0){
        result.emplace_back(index + n2 + 1);
    }
    //check not bottom 
    if (index -n2 - 1 >= 0 && index % n2 != 0 ){
        result.emplace_back(index -n2 - 1);
    }
    //check not bottom
    if (index + n2 - 1 <= maxIndex && index % n2 != 0){
        result.emplace_back(index + n2 - 1);
    }
    // check not top
    if (index -n2 + 1>= 0 && (index + 1)% n2 != 0){
        result.emplace_back(index - n2 + 1);
    }
    return result;

}
