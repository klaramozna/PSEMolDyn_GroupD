//
// Created by RayenManai on 04.01.24.
//
#pragma once
#include <memory>
#include <vector>
#include "../Particles/Particle.h"


class MembraneGenerator {
public:
    /**
     * @brief Creates a CuboidGenerator object initializing it with the given parameters.
     * @param corner represents the x, y and z coordinate of the left-lower corner of the front side of the cuboid.
     * @param n1 is the number of particles in x direction.
     * @param n2 is the number of particles in y direction.
     * @param n3 is the number of particles in z direction.
     * @param particleDistance is the distance between particles.
     * @param mass is the mass of each particle.
     * @param velocity is the initial velocity of each particle.
     * @param stiffness
     * @param bond_length
     */
    MembraneGenerator(std::array<double, 3> corner, int n1, int n2, int n3, double particleDistance, double mass, std::array<double, 3> velocity, double epsilon, double sigma, double stiffness, double bond_length, std::vector<std::array <int,3>> indices);

    /**
     * @brief Generates a cuboid of particles.
     * @return A vector with the generated particles.
     */
    std::vector<std::shared_ptr<Particle>> generateParticles(int type = 0);

    
    std::vector<std::shared_ptr<Particle>> calculateParallelNeighbourIndices (int n1, int n2, int n3, int index);

    std::vector<std::shared_ptr<Particle>> calculateDiagonalNeighbourIndices (int n1, int n2, int n3, int index);

    bool isHardcoded(int x, int y, int z, std::vector<std::array<int,3>> indices);

private:

    std::vector<std::shared_ptr<Particle>> particles;

    /**
     * @brief Coordinates of the left-lower corner of the front side of the cuboid.
     */
    std::array<double, 3> corner;

    /**
     * @brief Number of particles in the x direction.
     */
    int n1;

    /**
    * @brief Number of particles in the y direction.
    */
    int n2;

    /**
    * @brief Number of particles in the z direction.
    */
    int n3;

    /**
     * @brief Distance between particles.
     */
    double particleDistance;

    /**
     * @brief Mass of each particle.
     */
    double mass;

    /**
     * @brief Initial velocity of each particle.
     */
    std::array<double, 3> velocity;

    /**
     * @brief Epsilon of each particle.
     */
    double epsilon;

    /**
     * @brief Sigma of each particle.
     */
    double sigma;
     /**
     * @brief Stiffness constant of each particle.
     */
    double stiffness;
     /**
     * @brief Average bond length of each particle.
     */
    double bond_length;

    std::vector<std::array <int,3>> indices;
};

