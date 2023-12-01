//
// Created by klara on 22.11.23.
//

#include "LinkedCellContainer.h"
#include "utils/VectorDouble3.h"
#include <stdexcept>
#include <cmath>


//TODO:
// 1. Initialize grid -> right now, there would be an outOfBounds problem because grid hasn't been initialized
// 2. Define the behaviour of getParticleVector() -> I would return a copy, but that requires changing ParticleContainer and adapting
// existing code

LinkedCellContainer::LinkedCellContainer(CuboidBoundary boundary, double cutoffRadius,
                                         const std::vector<Particle>& particles) : boundary{boundary}, cutoffRadius{cutoffRadius} {
    size = particles.size();
    cellSize = cutoffRadius;

    // Calculate number of cells in each axis
    for (int i = 0; i < 3; i++) {
        nc[i] = std::floor(boundary.getDimensions()[i] / cellSize) == boundary.getDimensions()[i] / cellSize ? boundary.getDimensions()[i] + 2 : boundary.getDimensions()[i] + 3;
    }

    // Defines by how much each dimension in the grid needs to be shifted so that the grid is symmetrical to the boundary
    for (int i = 0; i < 3; i++) {
        gridShift[i] = 1 + (nc[i] * cellSize - boundary.getDimensions()[i]) / 2;
    }

    // Initialize grid
    grid.resize(nc[0] * nc[1] * nc[2]);

    // Populate boundaryCells
    for (int x = 0; x < nc[0]; ++x) {
        for (int y = 0; y < nc[1]; ++y) {
            for (int z = 0; z < nc[2]; ++z) {
                if (isBoundaryCell(x, y, z)) {
                    boundaryCells.push_back(grid[getGridIndex(x, y, z)]);
                }
            }
        }
    }

    putParticlesToCells(particles);
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
    for(int x = 0; x < nc[0]; x++){
        for(int y = 0; y < nc[1]; y++){
            for(int z = 0; z < nc[2]; z++){
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
    return x + nc[0] * (y + nc[1] * z);
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

/* Shouldn't generate any big problems */
void LinkedCellContainer::applyToBoundary(const std::function<void(Particle (&))> &function) {
    for (auto & boundaryCell : boundaryCells) {
        for (auto & particle : boundaryCell) {
            function(particle);
        }
    }
}


/* Not sure if this is a great idea, but alas */
void LinkedCellContainer::deleteHaloParticles() {
    for (auto & cell : grid) {
        for (auto & particle : cell) {
            if (!boundary.isInside(particle)) {
                cell.deleteParticle(particle);
            }
        }
    }
}

bool LinkedCellContainer::isBoundaryCell(int x, int y, int z) {
    return x == 0 || x == nc[0] - 1 || y == 0 || y == nc[1] - 1 || z == 0 || z == nc[2] - 1;
}

void LinkedCellContainer::addParticle(const Particle &p) {
    grid[getParticleIndex(p)].addParticle(p);
    size++;
}

std::vector<Cell> LinkedCellContainer::getCells() {
    return grid;
}