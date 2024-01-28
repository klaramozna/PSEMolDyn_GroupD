//
// Created by rodff on 26.01.24.
//

#include "ParallelizationStrategy.h"
#include <omp.h>

#ifdef _OPENMP
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

#endif

void CellwiseStrategy::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    auto& grid = container.grid;
    auto& nc = container.nc;
    // Iterate over all cells in parallel
    #pragma omp parallel default(none) shared(grid) firstprivate(function, nc)
    {
        #pragma omp for collapse(3) schedule(runtime)
        for (int z = 0; z < nc[2]; z++) {
            for (int y = 0; y < nc[1]; y++) {
                for (int x = 0; x < nc[0]; x++) {
                    // Find out where is the current cell in the grid vector
                    int currentGridIndex = container.getGridIndex(x, y, z);

                    // Apply function within current cell
                    grid[currentGridIndex].applyToPairs(function);
                }
            }
        }

        #pragma omp barrier

        #pragma omp for collapse(3) schedule(runtime)
        for (int z = 0; z < nc[2]; z++) {
            for (int y = 0; y < nc[1]; y++) {
                for (int x = 0; x < nc[0]; x++) {
                    // Find out where is the current cell in the grid vector
                    int currentGridIndex = container.getGridIndex(x, y, z);
                    for (auto &pCurrent: grid[currentGridIndex]) {
                        std::vector<int> indicesToLock{currentGridIndex};
                        // Find neighbours
                        for (int i = z - 1; i <= z + 1; i++) {
                            for (int j = y - 1; j <= y + 1; j++) {
                                for (int k = x - 1; k <= x + 1; k++) {

                                    int neighbourGridIndex = container.getGridIndex(k, j, i);

                                    if (neighbourGridIndex != currentGridIndex) {
                                        indicesToLock.push_back(neighbourGridIndex);
                                    }

                                    // Check if the neighbour has not yet been iterated over and if it is still inside of the grid
                                    if (neighbourGridIndex > currentGridIndex &&
                                        (k >= 0 && j >= 0 && i >= 0 && k < nc[0] && j < nc[1] && i < nc[2])) {
#ifdef _OPENMP
                                        acquireSortedLocks(container.cellLocks, indicesToLock);
#endif
                                        // Iterate over neighbour
                                        for (auto &pNeighbour: grid[neighbourGridIndex]) {
                                            // Apply function
                                            if (pCurrent != pNeighbour &&
                                                container.particleWithinCutoff(pCurrent, pNeighbour)) {
                                                function(pCurrent, pNeighbour);
                                            }
                                        }
#ifdef _OPENMP
                                        releaseLocks(container.cellLocks, indicesToLock);
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


void SubdomainStrategy::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    auto& grid = container.grid;
    auto subdomainSize = container.subdomain;

    #pragma omp parallel for default(none) shared(grid) firstprivate(function, subdomainSize) collapse(3) schedule(runtime)
    for (int z = 0; z < container.nc[2]; z += container.subdomain[2]) {
        for (int y = 0; y < container.nc[1]; y += container.subdomain[1]) {
            for (int x = 0; x < container.nc[0]; x += container.subdomain[2]) {

                // Iterate over the cells within the current subdomain
                for (int i = 0; i < container.subdomain[2]; i++) {
                    for (int j = 0; j < container.subdomain[1]; j++) {
                        for (int k = 0; k < container.subdomain[0]; k++) {
                            int currentX = x + k;
                            int currentY = y + j;
                            int currentZ = z + i;

                            // Ensure that the current cell is within the domain
                            if (currentX < container.nc[0] && currentY < container.nc[1] && currentZ < container.nc[2]) {
                                // Find out where is the current cell in the grid vector
                                int currentGridIndex = container.getGridIndex(currentX, currentY, currentZ);

#ifdef _OPENMP
                                omp_set_lock(&container.cellLocks[currentGridIndex]);
#endif
                                container.grid[currentGridIndex].applyToPairs(function);
#ifdef _OPENMP
                                omp_unset_lock(&container.cellLocks[currentGridIndex]);
#endif


                                std::vector<int> indicesToLock{currentGridIndex};
                                // Iterate over current cell
                                for (auto& pCurrent : container.grid[currentGridIndex]) {
                                    // Find neighbors
                                    for (int m = currentZ - 1; m <= currentZ + 1; m++) {
                                        for (int n = currentY - 1; n <= currentY + 1; n++) {
                                            for (int o = currentX - 1; o <= currentX + 1; o++) {
                                                int neighbourX = o;
                                                int neighbourY = n;
                                                int neighbourZ = m;

                                                // Ensure that the neighbor is within the domain
                                                if (neighbourX >= 0 && neighbourY >= 0 && neighbourZ >= 0 &&
                                                    neighbourX < container.nc[0] && neighbourY < container.nc[1] && neighbourZ < container.nc[2]) {

                                                    int neighbourGridIndex = container.getGridIndex(neighbourX, neighbourY, neighbourZ);

                                                    if (neighbourGridIndex != currentGridIndex) {
                                                        indicesToLock.push_back(neighbourGridIndex);
                                                    }

                                                    // Check if the neighbor has not yet been iterated over
                                                    if (neighbourGridIndex > currentGridIndex) {
#ifdef _OPENMP
                                                        acquireSortedLocks(container.cellLocks, indicesToLock);
#endif
                                                        // Iterate over neighbor
                                                        for (auto& pNeighbour : container.grid[neighbourGridIndex]) {
                                                            // Apply function
                                                            if (pCurrent != pNeighbour &&
                                                                    container.particleWithinCutoff(pCurrent, pNeighbour)) {
                                                                function(pCurrent, pNeighbour);
                                                            }
                                                        }
#ifdef _OPENMP
                                                        releaseLocks(container.cellLocks, indicesToLock);
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
}

void NonParallelStrategy::applyToPairs(const std::function<void(Particle &, Particle &)> &function) {
    CellwiseStrategy strat(this->container);
    strat.applyToPairs(function);
}
