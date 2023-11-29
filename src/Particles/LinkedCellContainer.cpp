//
// Created by klara on 22.11.23.
//

#include "LinkedCellContainer.h"
#include "utils/VectorDouble3.h"
#include <stdexcept>
#include <cmath>


LinkedCellContainer::LinkedCellContainer(const CuboidBoundary& boundary, double cutoffRadius,
                                         const std::vector<Particle>& particles) {
    this->cutoffRadius = cutoffRadius;
    size = particles.size();
    cellSize = cutoffRadius;
    numCellsX = std::floor(boundary.getWidth() / cellSize) == boundary.getWidth() / cellSize ? boundary.getWidth() + 2 : boundary.getWidth() + 3;
    numCellsY = std::floor(boundary.getHeight() / cellSize) == boundary.getHeight() / cellSize ? boundary.getHeight() + 2 : boundary.getHeight() + 3;
    numCellsZ = std::floor(boundary.getDepth() / cellSize) == boundary.getDepth() / cellSize ? boundary.getDepth() + 2 : boundary.getDepth() + 3;
    gridShift[0] = 1 + (numCellsX * cellSize - boundary.getWidth()) / 2;
    gridShift[1] = 1 + (numCellsY * cellSize - boundary.getHeight()) / 2;
    gridShift[2] = 1 + (numCellsZ * cellSize - boundary.getDepth()) / 2;
    putParticlesToCells(particles);
}

void LinkedCellContainer::addParticle(const Particle &p) {
    grid[getParticleIndex(p)].addParticle(p);
    size++;
}

size_t LinkedCellContainer::getSize() {
    return size;
}

std::vector<Particle> &LinkedCellContainer::getParticleVector() {
    /*std::vector<Particle> result{};
    for(auto & it : grid){
        result.insert(result.end(), it.begin(), it.end());
    }
    return result;*/
    //TODO: does it need to be a reference
}

void LinkedCellContainer::updateCells() {
    for(int i = 0; i < grid.size(); i++){
        for(auto & it : grid[i]){
            if(getParticleIndex(it) != i){  // particle isn't in the correct cell
                moveParticle(it, i, getParticleIndex(it));
            }
        }
    }
}

void LinkedCellContainer::moveParticle(const Particle &p1, int oldCell, int newCell) {
    grid[oldCell].deleteParticle(p1);
    grid[newCell].addParticle(p1);
}

void LinkedCellContainer::putParticlesToCells(const std::vector<Particle> &particles) {
    for(auto & p : particles){
        int index = getParticleIndex(p);
        grid[index].addParticle(p);
    }
}

void LinkedCellContainer::applyToAll(const std::function<void(Particle &)> &function) {
    // Creating a vector for marking particles that need to be moved
    std::vector<std::pair<Particle, int>> particlesToBeMoved{}; // stores each particle that needs to be moved with the cell it's beeing moved from
    particlesToBeMoved.reserve(size);

    // Applying given function to each particle and marking particles for movement
    for(int i = 0; i < grid.size(); i++){
        for(auto & particle : grid[i]){
            function(particle);
            if(!isInCorrectCell(particle, i)){
                particlesToBeMoved.emplace_back(particle, i);
            }
        }
    }

    // Moving particles to their new cells
    for(auto & particle : particlesToBeMoved){
        moveParticle(particle.first, particle.second, getParticleIndex(particle.first));
    }
}

bool LinkedCellContainer::isInCorrectCell(const Particle &p, int currentIndex) {
    return getParticleIndex(p) == currentIndex;
}

void LinkedCellContainer::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    // Iterate over positions
    for(int x = 0; x < numCellsX; x++){
        for(int y = 0; y < numCellsY; y++){
            for(int z = 0; z < numCellsZ; z++){
                // Find out where is the current cell in the grid vector
                int currentGridIndex = getGridIndex(x, y, z);
                // Iterate over current cell
                for(auto & pCurrent : grid[currentGridIndex]){
                    // Find neighbours
                    for(int i = x - 1; i < x + 1; i++){
                        for(int j = y - 1; j < y + 1; j++){
                            for(int k = z - 1; k < z + 1; k++){
                                // Iterate over neighbour
                                if(cellWithinRadius(pCurrent, i, j, k)){
                                    for(auto & pNeighbour : grid[getGridIndex(i, j, k)]){
                                        // Apply function
                                        if(pCurrent != pNeighbour && particleWithinCutoff(pCurrent, pNeighbour)){
                                            function(pCurrent, pNeighbour);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int LinkedCellContainer::getGridIndex(int x, int y, int z) const {
    return x + numCellsX * (y + numCellsY * z);
}

bool LinkedCellContainer::particleWithinCutoff(const Particle &p1, const Particle &p2) const {
    return getDistance(p1.getXVector(), p2.getXVector()) <= cutoffRadius;
}

int LinkedCellContainer::getParticleIndex(const Particle &p) {
    int x = floor((p.getX()[0] + gridShift[0]) / cellSize);
    int y = floor((p.getX()[1] + gridShift[1]) / cellSize);
    int z = floor((p.getX()[2] + gridShift[2]) / cellSize);
    return getGridIndex(x, y, z);
}



