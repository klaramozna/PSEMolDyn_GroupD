//
// Created by klara on 22.11.23.
//

#include "LinkedCellContainer.h"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <memory>
#include <algorithm>

LinkedCellContainer::LinkedCellContainer(Boundary boundary, double cutoffRadius,
                                         const std::vector<Particle>& particles) : boundary{boundary}, grid{}, cutoffRadius{cutoffRadius} {
    size = particles.size();

    // Potencially slightly increase cell size (compared to cutoff radius)
    for(int i = 0; i < 3; i++){
        cellSize[i] = boundary.getDimensions()[i] / std::floor(boundary.getDimensions()[i] / cutoffRadius);
    }

    // Calculate number of cells in each axis
    for (int i = 0; i < 3; i++) {
        nc[i] = std::floor(boundary.getDimensions()[i] / cutoffRadius) + 2;
    }

    // Defines by how much each dimension in the grid needs to be shifted so that the grid is symmetrical to the boundary
    gridShift = cellSize;

    // Initialize grid
    grid.resize(nc[0] * nc[1] * nc[2], Cell{cutoffRadius});

    // Populate boundaryCells
    for (int x = 0; x < nc[0]; ++x) {
        for (int y = 0; y < nc[1]; ++y) {
            for (int z = 0; z < nc[2]; ++z) {
                if (isBoundaryCell(x, y, z)) {
                    boundaryCells_ptr.push_back(&grid[getGridIndex(x, y, z)]);
                }
            }
        }
    }

    addParticles(particles);
}



size_t LinkedCellContainer::getSize() {
    return size;
}

std::vector<Particle> LinkedCellContainer::getParticleVector() {
    std::vector<Particle> result{};
    for(auto & it : grid){
        for(const auto& itInner : it){
            result.push_back(*itInner);
        }
    }
    return result;
}

Particle LinkedCellContainer::getParticleWithId(int id) {
    for (auto &particle : getParticleVector()) {
        if (particle.getId() == id) 
            return particle;
    }
    //return fake particle
    Particle p{};
    p.setId(-1);
    return p;
}

void LinkedCellContainer::updateCells() {
    for(int i = 0; i < grid.size(); i++){
        for(auto & it : grid[i]){
            if(getParticleIndex(*it) != i){  // particle isn't in the correct cell
                moveParticle(it, i, getParticleIndex(*it));
            }
        }
    }
}

void LinkedCellContainer::moveParticle(std::shared_ptr<Particle> p1, int oldCell, int newCell) {
    grid[oldCell].deleteParticle(p1);

    // Check if particle is outside
    if (particleOutOfGrid(*p1)){
        size--;
    } else {
        grid[newCell].addParticle(p1);
    }
}

void LinkedCellContainer::applyToAll(const std::function<void(Particle &)> &function) {
    // Creating a vector for marking particles that need to be moved
    std::vector<std::pair<std::shared_ptr<Particle>, int>> particlesToBeMoved{}; // stores each particle that needs to be moved with the cell it's beeing moved from

    // Applying given function to each particle and marking particles for movement
    for(int i = 0; i < grid.size(); i++){
        for(auto & particle : grid[i]){
            function(*particle);
            if(!isInCorrectCell(*particle, i)){
                particlesToBeMoved.emplace_back(particle, i);
            }
        }
    }

    // Moving particles to their new cells
    for(auto & particle : particlesToBeMoved){
        moveParticle(particle.first, particle.second, getParticleIndex(*(particle.first)));
    }
}

bool LinkedCellContainer::isInCorrectCell(const Particle &p, int currentIndex) {
    return getParticleIndex(p) == currentIndex;
}

void LinkedCellContainer::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    // Iterate over all cells
    for(int z = 0; z < nc[2]; z++) {
        for (int y = 0; y < nc[1]; y++) {
            for (int x = 0; x < nc[0]; x++) {


                // Find out where is the current cell in the grid vector
                int currentGridIndex = getGridIndex(x, y, z);

                // Apply function within current cell
                grid[currentGridIndex].applyToPairs(function);

                // Iterate over current cell
                for (auto &pCurrent: grid[currentGridIndex]) {

                    // Find neighbours
                    for (int i = z - 1; i <= z + 1; i++) {
                        for (int j = y - 1; j <= y + 1; j++) {
                            for (int k = x - 1; k <= x + 1; k++) {

                                int neighbourGridIndex = getGridIndex(k, j, i);

                                // Check if the neighbour has not yet been iterated over and if it is still inside of the grid
                                if (neighbourGridIndex > currentGridIndex &&
                                    (k >= 0 && j >= 0 && i >= 0 && k < nc[0] && j < nc[1] && i < nc[2])) {

                                    // Iterate over neighbour
                                    for (auto &pNeighbour: grid[getGridIndex(k, j, i)]) {
                                        // Apply function
                                        if (pCurrent != pNeighbour && particleWithinCutoff(*pCurrent, *pNeighbour)) {
                                            function(*pCurrent, *pNeighbour);
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
    int x = floor((p.getX()[0] + gridShift[0]) / cellSize[0]);
    int y = floor((p.getX()[1] + gridShift[1]) / cellSize[1]);
    int z = floor((p.getX()[2] + gridShift[2]) / cellSize[2]);
    return getGridIndex(x, y, z);
}

void LinkedCellContainer::applyToBoundary(const std::function<void(Particle (&))> &function) {
    // Creating a vector for marking particles that need to be moved
    std::vector<std::pair<std::shared_ptr<Particle>, int>> particlesToBeMoved{}; // stores each particle that needs to be moved with the cell it's beeing moved from

    for (auto boundaryCell : boundaryCells_ptr) {
        if (boundaryCell != nullptr) {
            for (auto &particle : *boundaryCell) {
                int currentCell = getParticleIndex(*particle);
                function(*particle);
                if(!isInCorrectCell(*particle, currentCell)){
                    particlesToBeMoved.emplace_back(particle, currentCell);
                }
            }
        }
    }

    // Moving particles to their new cells
    for(auto & particle : particlesToBeMoved){
        moveParticle(particle.first, particle.second, getParticleIndex(*(particle.first)));
    }
}


/* Not sure if this is a great idea, but alas */
void LinkedCellContainer::deleteHaloParticles() {
    // Creating a vector for marking particles that need to be deleted
    std::vector<std::pair<std::shared_ptr<Particle>, int>> particlesToBeDeleted{}; // stores each particle that needs to be deleted with the cell it's beeing deleted from

    // Applying given function to each particle and marking particles for movement
    for(int i = 0; i < grid.size(); i++){
        for(auto & particle : grid[i]){
            if ((*particle).isMarkedForDeleting()) {
                particlesToBeDeleted.emplace_back(particle, i);
                continue;
            }
            if(boundary.isOutside(*particle)){
                if ((*particle).isMarkedForMirroring()) {
                    Particle p2 = mirrorParticle(*particle);
                    p2.unmarkForMirroring();
                    addParticle(p2);
                    size++;
                }
                particlesToBeDeleted.emplace_back(particle, i);
            }
        }
    }

    // Deleting halo particles
    for(auto & particle : particlesToBeDeleted){
        grid[particle.second].deleteParticle(particle.first);
        size--;
    }
}

bool LinkedCellContainer::isBoundaryCell(int x, int y, int z) {
    return (x == 1 || x == nc[0] - 2 || y == 1 || y == nc[1] - 2 || z == 1 || z == nc[2] - 2) && !(x == 0 || y == 0 || z == 0);
}

void LinkedCellContainer::addParticle(const Particle &p) {
    if(getParticleIndex(p) < 0 || getParticleIndex(p) >= grid.size()){
        throw std::runtime_error("Particle out of domain.");
    }

    grid[getParticleIndex(p)].addParticle(std::make_shared<Particle>(p));
    size++;
}

std::vector<Cell> LinkedCellContainer::getCells() {
    return grid;
}

bool LinkedCellContainer::cellWithinRadius(const Particle &p, int x, int y, int z) {
    double middleX = x * cellSize[0] - gridShift[0] + cellSize[0] / 2;
    double middleY = y * cellSize[1] - gridShift[1] + cellSize[1] / 2;
    double middleZ = z * cellSize[2] - gridShift[2] + cellSize[2] / 2;
    return particleWithinCutoff(p, Particle{std::array<double, 3>{middleX, middleY, middleZ}, std::array<double, 3>{}, 0});
}

bool LinkedCellContainer::particleOutOfGrid(const Particle &p) {
    std::array<double, 3> pos = p.getX();
    return pos[0] < -cellSize[0] || pos[0] > boundary.getDimensions()[0] + cellSize[0]
    || pos[1] < -cellSize[1] || pos[1] > boundary.getDimensions()[1] + cellSize[1]
    || pos[2] < -cellSize[2] || pos[2] > boundary.getDimensions()[2] + cellSize[2];
}

Particle LinkedCellContainer::mirrorParticle(const Particle &p) {
    double x = p.getX()[0];
    double y = p.getX()[1];
    double z = p.getX()[2];

    if (x < 0) {
        x += boundary.getDimensions()[0];
    } else if (x > boundary.getDimensions()[0]) {
        x -= boundary.getDimensions()[0];
    }

    if (y < 0) {
        y += boundary.getDimensions()[1];
    } else if (y > boundary.getDimensions()[1]) {
        y -= boundary.getDimensions()[1];
    }

    if (z < 0) {
        z += boundary.getDimensions()[2];
    } else if (z > boundary.getDimensions()[2]) {
        z -= boundary.getDimensions()[2];
    }

    return Particle{std::array<double, 3>{x, y, z}, p.getV(), p.getM(), p.getEpsilon(), p.getSigma(), p.getType()};
}

void LinkedCellContainer::addParticlePointer(std::shared_ptr<Particle> p) {
    if(getParticleIndex(*p) < 0 || getParticleIndex(*p) >= grid.size()){
        throw std::runtime_error("Particle out of domain.");
    }

    grid[getParticleIndex(*p)].addParticle(p);
    size++;
}



