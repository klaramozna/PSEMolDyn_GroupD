//
// Created by klara on 22.11.23.
//

#include "LinkedCellContainer.h"

#include <stdexcept>


LinkedCellContainer::LinkedCellContainer(CuboidBoundary boundary, double cutoffRadius,
                                         std::vector<Particle> particles) {
    numCellsX = boundary.getWidth() + 2;
    numCellsY = boundary.getHeight() + 2;
    numCellsZ = boundary.getDepth() + 2;
    this->cutoffRadius = cutoffRadius;
    size = particles.size();
    putParticlesToCells(particles);
}

void LinkedCellContainer::addParticle(const Particle &p) {
    grid[getCellIndex(p)].addParticle(p);
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
            if(getCellIndex(it) != i){  // particle isn't in the correct cell
                moveParticle(it, i, getCellIndex(it));
            }
        }
    }
}

void LinkedCellContainer::moveParticle(const Particle &p1, int oldCell, int newCell) {
    grid[oldCell].deleteParticle(p1);
    grid[newCell].addParticle(p1);
}

int LinkedCellContainer::getCellIndex(const Particle &p) const {
    // The plus one is there due to having one layer of halo cells outside of the domain
    int index = static_cast<int>(p.getX()[0] + 1) + numCellsX * (static_cast<int>(p.getX()[1] + 1) + numCellsY * static_cast<int>(p.getX()[2] + 1));
    if(index < 0 || index >= grid.size()){
        throw std::runtime_error("Particle is outside of grid and cannot be added.");
    }
    return index;
}

void LinkedCellContainer::putParticlesToCells(const std::vector<Particle> &particles) {
    for(auto & p : particles){
        int index = getCellIndex(p);
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
        moveParticle(particle.first, particle.second, getCellIndex(particle.first));
    }
}

bool LinkedCellContainer::isInCorrectCell(const Particle &p, int currentIndex) {
    return getCellIndex(p) == currentIndex;
}

void LinkedCellContainer::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    for(int i = 0; i < grid.size(); i++){
        // Apply the function on the pairs of particles within one cell
        grid[i].applyToPairs(function);

        // Iterate over neighbours within cutoff radius and apply function.
        std::vector<int> neighbours = getNeighbours(i);
        for(int j = 0; j < neighbours.size(); j++){
            grid[i].interactWithCell(grid[j], function);
        }
    }
}


