//
// Created by klara on 22.11.23.
//

#include "LinkedCellContainer.h"
#include <stdexcept>
#include <cmath>

#include <omp.h>

// Helper function to sort indices and acquire locks
void acquireSortedLocks(std::vector<omp_lock_t>& cellLocks, const std::vector<int>& indices) {
    std::vector<int> sortedIndices = indices;
    std::sort(sortedIndices.begin(), sortedIndices.end());
    for (int index : sortedIndices) {
        omp_set_lock(&cellLocks[index]);
    }
}

// Helper function to release locks
void releaseLocks(std::vector<omp_lock_t>& cellLocks, const std::vector<int>& indices) {
    for (int index : indices) {
        omp_unset_lock(&cellLocks[index]);
    }
}


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

#ifdef _OPENMP
    const int totalCells = getCells().size();

    int cellsPerThread = totalCells / omp_get_max_threads();

    // Adjust subdomain size to achieve a balanced distribution
    while (subdomainSizeX * subdomainSizeY * subdomainSizeZ < cellsPerThread) {
        if (subdomainSizeX < nc[0]) subdomainSizeX++;
        if (subdomainSizeY < nc[1]) subdomainSizeY++;
        if (subdomainSizeZ < nc[2]) subdomainSizeZ++;
    }

    cellLocks.resize(grid.size());
    for (auto &lock : cellLocks) {
        omp_init_lock(&lock);
    }
#endif
}



size_t LinkedCellContainer::getSize() {
    return size;
}

std::vector<Particle> LinkedCellContainer::getParticleVector() {
    std::vector<Particle> result{};
    for(auto & it : grid){
        result.insert(result.end(), it.begin(), it.end());
    }
    return result;
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

    // Check if particle is outside
    if (particleOutOfGrid(p1)){
        size--;
    } else {
        grid[newCell].addParticle(p1);
    }
}

void LinkedCellContainer::applyToAll(const std::function<void(Particle &)> &function) {
    // Vector to store particles that need to be moved
    std::vector<std::vector<std::pair<Particle, int>>> localParticlesToBeMoved(omp_get_max_threads());

    #pragma omp parallel for schedule(static, 1) default(none) shared(grid, localParticlesToBeMoved, function)
    for (int i = 0; i < grid.size(); i++) {
        for (auto &particle: grid[i]) {
            int thread_id = omp_get_thread_num();
            function(particle);
            if (!isInCorrectCell(particle, i)) {
                localParticlesToBeMoved[thread_id].emplace_back(particle, i);
            }
        }
    }

    // Moving particles to their new cells
    for (const auto &vector : localParticlesToBeMoved) {
        for (const auto &particleInfo: vector) {
            moveParticle(particleInfo.first, particleInfo.second, getParticleIndex(particleInfo.first));
        }
    }
}

bool LinkedCellContainer::isInCorrectCell(const Particle &p, int currentIndex) {
    return getParticleIndex(p) == currentIndex;
}

void LinkedCellContainer::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    // Iterate over all cells
    #pragma omp parallel for schedule(static, 1) default(none) shared(grid, Logger::console) firstprivate(function, subdomainSizeY, subdomainSizeZ, subdomainSizeX, nc) collapse(3)
    for (int z = 0; z < nc[2]; z += subdomainSizeZ) {
        for (int y = 0; y < nc[1]; y += subdomainSizeY) {
            for (int x = 0; x < nc[0]; x += subdomainSizeX) {

                // Iterate over the cells within the current subdomain
                for (int i = 0; i < subdomainSizeZ; i++) {
                    for (int j = 0; j < subdomainSizeY; j++) {
                        for (int k = 0; k < subdomainSizeX; k++) {
                            int currentGridIndex = getGridIndex(x+k, y+j, z+i);
                            if (currentGridIndex < grid.size()) {
                                // Apply function within current cell
#ifdef _OPENMP
                                Logger::console->debug("Thread {} is acquiring lock on cell {}", omp_get_thread_num(),
                                                       currentGridIndex);
                                omp_set_lock(&cellLocks[currentGridIndex]);
                                Logger::console->debug("Thread {} holds lock on cell {}", omp_get_thread_num(),
                                                       currentGridIndex);
#endif
                                grid[currentGridIndex].applyToPairs(function);
#ifdef _OPENMP
                                omp_unset_lock(&cellLocks[currentGridIndex]);
                                Logger::console->debug("Thread {} released lock on cell {}", omp_get_thread_num(),
                                                       currentGridIndex);
#endif

                            }
                        }
                    }
                }

                for (int i = 0; i < subdomainSizeZ; i++) {
                    for (int j = 0; j < subdomainSizeY; j++) {
                        for (int k = 0; k < subdomainSizeX; k++) {
                            int currentX = x + k;
                            int currentY = y + j;
                            int currentZ = z + i;

                            int currentGridIndex = getGridIndex(currentX, currentY, currentZ);

                            // Iterate over current cell

                            if (currentGridIndex < grid.size()) {
                                for (auto &pCurrent: grid[currentGridIndex]) {
                                    std::vector<int> indicesToLock{currentGridIndex};
                                    for (int m = currentZ - 1; m <= currentZ + 1; m++) {
                                        for (int n = currentY - 1; n <= currentY + 1; n++) {
                                            for (int o = currentX - 1; o <= currentX + 1; o++) {
                                                int neighbourX = o;
                                                int neighbourY = n;
                                                int neighbourZ = m;

                                                // Check if the neighbour has not yet been iterated over and if it is still inside of the grid
                                                if (neighbourX >= 0 && neighbourY >= 0 && neighbourZ >= 0 &&
                                                    neighbourX < nc[0] && neighbourY < nc[1] && neighbourZ < nc[2]) {

                                                    int neighbourGridIndex = getGridIndex(neighbourX, neighbourY,
                                                                                          neighbourZ);
                                                    if (neighbourGridIndex != currentGridIndex) {
                                                        indicesToLock.push_back(neighbourGridIndex);
                                                    }

                                                    // Iterate over neighbour
#ifdef _OPENMP
                                                    Logger::console->debug("Thread {} is acquiring locks on cells {}, {}", omp_get_thread_num(),
                                                                           indicesToLock[0], indicesToLock[1]);
                                                    acquireSortedLocks(cellLocks, indicesToLock);
                                                    Logger::console->debug("Thread {} holds locks on cells {}, {}", omp_get_thread_num(),
                                                                           indicesToLock[0], indicesToLock[1]);
#endif
                                                    for (auto &pNeighbour: grid[neighbourGridIndex]) {
                                                        // Apply function
                                                        if (pCurrent != pNeighbour &&
                                                            particleWithinCutoff(pCurrent, pNeighbour)) {
                                                            function(pCurrent, pNeighbour);
                                                        }
                                                    }
#ifdef _OPENMP
                                                    releaseLocks(cellLocks, indicesToLock);
                                                    Logger::console->debug("Thread {} released locks on cells {}, {}", omp_get_thread_num(),
                                                                           indicesToLock[0], indicesToLock[1]);
#endif
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

void LinkedCellContainer::applyToBoundary(const std::function<void(Particle &)> &function) {
    // Vector to store particles that need to be moved
    std::vector<std::vector<std::pair<Particle, int>>> localVector_particlesToBeMoved(omp_get_max_threads());

    #pragma omp parallel default(none) shared(boundaryCells_ptr, localVector_particlesToBeMoved, function)
    {
        int thread_id = omp_get_thread_num();

        #pragma omp for schedule(static,1) nowait
        for (auto boundaryCell : boundaryCells_ptr) {
            if (boundaryCell != nullptr) {
                for (auto &particle : *boundaryCell) {
                    int currentCell = getParticleIndex(particle);
                    function(particle);
                    if (!isInCorrectCell(particle, currentCell)) {
                        localVector_particlesToBeMoved[thread_id].emplace_back(particle, currentCell);
                    }
                }
            }
        }
    }

    // Moving particles to their new cells
    for (const auto &vector : localVector_particlesToBeMoved) {
        for (const auto &particleInfo: vector) {
            moveParticle(particleInfo.first, particleInfo.second, getParticleIndex(particleInfo.first));
        }
    }
}



/* Not sure if this is a great idea, but alas */
void LinkedCellContainer::deleteHaloParticles() {
    // Creating a vector for marking particles that need to be deleted
    std::vector<std::pair<Particle, int>> particlesToBeDeleted{}; // stores each particle that needs to be deleted with the cell it's beeing deleted from

    // Applying given function to each particle and marking particles for movement
    for(int i = 0; i < grid.size(); i++){
        for(auto & particle : grid[i]){
            if (particle.isMarkedForDeleting()) {
                particlesToBeDeleted.emplace_back(particle, i);
                continue;
            }
            if(boundary.isOutside(particle)){
                if (particle.isMarkedForMirroring()) {
                    Particle p2 = mirrorParticle(particle);
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
    grid[getParticleIndex(p)].addParticle(p);
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



