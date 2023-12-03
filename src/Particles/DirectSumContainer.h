//
// Created by klara on 30.10.23.
//

#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleContainer.h"
#include "Simulation/Physics/ForceCalculation.h"
#include <functional>

/**
 * @file DirectSumContainer.h
 *
 * @brief Hides structure / implementation of particles.
 */


class DirectSumContainer : public ParticleContainer{
private:
    /**
     * @brief Stores the particles.
     */
    std::vector<Particle> particles;
public:
    class PairIterator;

    using iterator_type = std::vector<Particle>::iterator;

    /**
     * @brief Creates a container, using the given vector to initialize particles.
     * @param particles stores the particles.
     */
    explicit DirectSumContainer(std::vector<Particle> particles);

    DirectSumContainer() = default;

    /**
     * @brief Creates an iterator at the starting position.
     * @return the iterator.
     */
    iterator_type begin();

    /**
     * @brief Creates an iterator pointing behind the last particle.
     * @return the iterator.
     */
    iterator_type end();

    /**
     * @brief Wrapper for std::vector::reserve(size_type n)
     * @param n Number of elements to have capacity for
     * */
    void reserveInVector(size_t n);

    /**
     * @brief Adds the given particle to the collection.
     * @param particle is the particle to be added.
     */
    void addParticle(const Particle& particle) override;

    /**
     * @brief Fuses another DirectSumContainer onto the colllection.
     * @param container another particle container passed as reference
     * */
    void addParticles(const DirectSumContainer &container);

    /**
     * @brief returns the size of the underlying particle vector
     * */
    size_t getSize() override;

    /**
     * @brief Creates an iterator for pairs of particles at the starting position
     * @return the iterator.
     */
    PairIterator beginPair();

    /**
     * @brief Creates an iterator for pairs pointing behind the last pair of particles.
     * @return the iterator.
     */
    PairIterator endPair();

    /**
     * @brief Returns a vector of all stored particles.
     * @return the vector.
     */
    std::vector<Particle> &getParticleVector() override;

    /**
     * @brief Applies the given function to all particles
     * @param function is the function to be used on the particles
     */
    void applyToAll(const std::function<void(Particle&)>& function) override;

    /**
     * @brief Applies the given function to all distinct pairs of particles
     * @param function is the function to be applied to the particle pairs
     */
    void applyToPairs(const std::function<void(Particle&, Particle&)>& function) override;

    /**
     * @brief Processes the boundary (in this direct sum implementation, it does nothimg
     * @param forceCalculation determines what type of force should be applied to enforce the boundary
     * */
     void applyBoundaryConditions(Boundary& Boundary) override;

    /**
     * @brief Implements an iterator that simulated a nested loop (two for loops), but skips the case where the particle in the outer loop is the same as the particle in the inner loop.
     */
    class PairIterator {
    private:
        /**
         * @brief Specifies the position in the outer loop.
         */
        std::vector<Particle>::size_type outerIndex;
        /**
         * @brief Specifies the position in the inner loop.
         */
        std::vector<Particle>::size_type innerIndex;
        /**
         * @brief Stores a reference to the particles.
         */
        std::vector<Particle> &p;

        /**
         * @brief Returns true if the iterator can be safely dereferenced.
         * @return the resulting value.
         */
        bool inRange() const;

    public:
        /**
         * @brief Creates an iterator at the given position.
         * @param outer is the position in the outer loop.
         * @param inner is the position in the inner loop.
         * @param vec contains the particles that are iterated over.
         */
        PairIterator(std::vector<Particle>::size_type outer, std::vector<Particle>::size_type inner,
                     std::vector<Particle> &vec);

        /**
         * @brief Returns a pair of particles at the position of the iterator.
         * @return The first particle is the one in the outer loop, the second one in the inner loop.
         */
        std::pair<Particle &, Particle &> operator*() const;

        /**
         * @brief Increments the iterator.
         * @return The incremented iterator.
         */
        PairIterator &operator++();

        /**
         * @brief Checks if the two iterators are equal.
         * @param a Left iterator.
         * @param b Right iterator.
         * @return Returns true if they are equal and false otherwise.
         */
        friend bool operator==(const PairIterator &a, const PairIterator &b);

        /**
         * @brief Checks if the two iterators are not equal.
         * @param a Left iterator.
         * @param b Right iterator.
         * @return Returns true if they are not equal and false otherwise
         */
        friend bool operator!=(const PairIterator &a, const PairIterator &b);
    };
};
