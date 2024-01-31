//
// Created by rodff on 26.01.24.
//

#pragma once

#include <functional>
#include "Particle.h"

#include "LinkedCellContainer.h"
#include "../utils/ParallelizationSpec.h"

class ParallelizationStrategy {
public:
    ParallelizationStrategy(LinkedCellContainer &container) : container(container) {};
    virtual void applyToPairs(const std::function<void(Particle&, Particle&)>& function) = 0;
    virtual ~ParallelizationStrategy() = default;
protected:
    LinkedCellContainer &container;
};

class CellwiseStrategy : public ParallelizationStrategy {
public:
    CellwiseStrategy(LinkedCellContainer& container) : ParallelizationStrategy(container) {}

    /**
     * @brief Implements the applyToPairs algorithm in a cellwise fashion, meaning threads get assigned individual cells
     * @param function
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;
};


class SubdomainStrategy : public ParallelizationStrategy {
public:
    SubdomainStrategy(LinkedCellContainer& container) : ParallelizationStrategy(container) {}
    /**
     * @brief Implements the applyToPairs algorithm in a subdomainwise fashion, meaning threads get assigned neighboured cell sets
     * @param function
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;
};

class NonParallelStrategy : public ParallelizationStrategy {
public:
    NonParallelStrategy(LinkedCellContainer& container) : ParallelizationStrategy(container) {}

    // Implementation for non-parallel processing
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;
};
