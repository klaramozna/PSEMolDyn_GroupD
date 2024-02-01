/*
 * Particle.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include <array>
#include <string>
#include <memory>
#include "../utils/VectorDouble3.h"

class Particle {

private:
    /**
     * Position of the particle
     */
    VectorDouble3 x;

    /**
     * Velocity of the particle
     */
    VectorDouble3 v;

    /**
     * Force effective on this particle
     */
    VectorDouble3 f;

    /**
     * Force which was effective on this particle
     */
    VectorDouble3 old_f;

    /**
     * Mass of this particle
     */
    double m;

    /**
     * Bool value that determines whether particle should be mirrored
     */
     bool markedForMirroring;

    /**
     * @brief Epsilon for lennard jones forces.
     */
    double epsilon;

    /**
     * @brief Sigma for lennard jones forces.
     */
    double sigma;   

    /**
     * @brief k: the stiffness constant
     */
    double stiffness;

    /**
     * @brief  r0: the average bond length of a molecule pair
     */
    double bond_length;

    /**    
     * pointers to the direct parallel neighbours of this particle
     */
    std::vector<std::shared_ptr<Particle>> parallel_Neighbours;

    /**
     * pointers to the direct diagonal neighbours of this particle
     */
    std::vector<std::shared_ptr<Particle>> diagonal_Neighbours;
    /**
     * unique identifier of each particle (can be used in membrane to keep track of neighbours) 
     */
    int id;


    /**
     * @brief Indicates if the particle is a wall-particle (not affected by thermostat, does not move etc.)
     */
    bool isWall;
    /**
     * Type of the particle. Use it for whatever you want (e.g. to separate
     * molecules belonging to different bodies, matters, and so on)
     */
    int type;

    bool markedForDeleting;

    
    bool hardcode_flag;


public:
    explicit Particle(int type = 0);

    Particle(const Particle &other);

    Particle(
            // for visualization, we need always 3 coordinates
            // -> in case of 2d, we use only the first and the second
            std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg,
            int type = 0, bool wall = false);

    /**
     * @brief Creates a Particle object using the given parameters.
     * @param x_arg The position of the particle.
     * @param v_arg The velocity of the particle.
     * @param m_arg The mass of the particle.
     * @param epsilon The epsilon (for Lennard-Jones calculation) of the particle.
     * @param sigma The sigma (for Lennard-Jones calculation) of the particle.
     * @param type The type of the particle.
     */
    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg, double epsilon, double sigma,
             int type = 0, bool wall = false): x{x_arg}, v{v_arg}, f{VectorDouble3(std::array<double, 3>{0, 0, 0})}, old_f{VectorDouble3(std::array<double, 3>{0, 0, 0})}, m{m_arg}, epsilon{epsilon}, sigma{sigma}, type{type} {
        markedForMirroring = false;
        markedForDeleting = false;
        isWall = wall;
    };

    /**
     * @brief Creates a Particle object using the given parameters.
     * @param x_arg The position of the particle.
     * @param v_arg The velocity of the particle.
     * @param m_arg The mass of the particle.
     * @param epsilon The epsilon (for Lennard-Jones calculation) of the particle.
     * @param sigma The sigma (for Lennard-Jones calculation) of the particle.
     * @param stiffness_arg parallel neighbours 
     * @param bond_length_arg diagonal neighbours
     * @param parallel_Neighbours_arg parallel neighbours 
     * @param diagonal_Neighbours_arg diagonal neighbours
     * @param id_arg unique id of this particle
     * @param type The type of the particle.
     */
    Particle(std::array<double, 3> x_arg, std::array<double, 3> v_arg, double m_arg, double epsilon, double sigma,
            double stiffness_arg, double bond_length_arg, std::vector<std::shared_ptr<Particle>> parallel_Neighbours_arg, std::vector<std::shared_ptr<Particle>> diagonal_Neighbours_arg, int id, bool hardcode_flag, int type = 0): x{x_arg}, v{v_arg}, f{VectorDouble3(std::array<double, 3>{0, 0, 0})}, old_f{VectorDouble3(std::array<double, 3>{0, 0, 0})}, m{m_arg}, epsilon{epsilon}, sigma{sigma},stiffness{stiffness_arg}, bond_length{bond_length_arg} ,parallel_Neighbours{parallel_Neighbours_arg}, diagonal_Neighbours{diagonal_Neighbours_arg}, id{id}, type{type}, hardcode_flag{hardcode_flag}  {
        markedForMirroring = false;
        markedForDeleting = false;
        isWall = false;
    };

    virtual ~Particle();

    const std::array<double, 3> getX() const;

    const std::array<double, 3> getV() const;

    const std::array<double, 3> getF() const;

    const std::array<double, 3> getOldF() const;

    bool isMarkedForMirroring() const;

    double getEpsilon() const{return epsilon;}

    double getSigma() const{return sigma;}

    bool isWallParticle() const{return isWall;};

    /**
     * @brief Returns the position as a DoubleVector.
     * @return Vector with the values of the position
     */
    VectorDouble3 getXVector() const;

    /**
     * @brief Returns the velocity as a DoubleVector.
     * @return Vector with the values of the velocity
     */
    VectorDouble3 getVVector() const;

    /**
     * @brief Returns the force as a DoubleVector.
     * @return Vector with the values of the force
     */
    VectorDouble3 getFVector() const;

    /**
     * @brief Returns the position in the previous iteration as a DoubleVector.
     * @return Vector with the values of the force.
     */
    VectorDouble3 getOldFVector() const;

    double getM() const;

    int getType() const;

    double getStiffness() const;

    double getBondLength() const;

    int getId() const;

    bool getHardcodeFlag() const;

    /**
     * @brief Returns a vector with the pointers to the parallel neighbours of this particle
     * @return Vector with these pointers.
     */
    std::vector<std::shared_ptr<Particle>> getParallelNeighbours() const;

    /**
     * @brief Returns a vector with the pointers to the diagonal neighbours of this particle
     * @return Vector with these pointers.
     */
    std::vector<std::shared_ptr<Particle>> getDiagonalNeighbours() const;

    /**
     * @brief Sets the values of the position based on the given vector.
     * @param position contains the values that will be assigned to the position, needs to be of size 3.
     */
    void setX(const VectorDouble3 &position);

    /**
     * @brief Sets the values of the velocity based on the given vector.
     * @param position contains the values that will be assigned to the velocity, needs to be of size 3.
     */
    void setV(const VectorDouble3 &velocity);

    /**
     * @brief Sets the values of the force based on the given vector.
     * @param position contains the values that will be assigned to the force, needs to be of size 3.
     */
    void setF(const VectorDouble3 &force);

    /**
     * @brief Sets the values of the force in the previous iteration based on the given vector.
     * @param position contains the values that will be assigned to the force, needs to be of size 3.
     */
    void setOldF(const VectorDouble3 &oldForce);

    /**
     * @brief Sets the values of position according to the given parameters.
     * @param x x coordinate
     * @param y y coordinate
     * @param z z coordinate
     */
    void setX(double x, double y, double z);

    /**
     * @brief Sets the values of velocity according to the given parameters.
     * @param x velocity in the x-direction.
     * @param y velocity in the y-direction.
     * @param z velocity in the z-direction.
     */
    void setV(double x, double y, double z);

    /**
     * @brief Sets the values of force according to the given parameters.
     * @param x force in the x-direction.
     * @param y force in the y-direction.
     * @param z force in the z-direction.
     */
    void setF(double x, double y, double z);

    /**
     * @brief Sets the values of force in the previous iteration according to the given parameters.
     * @param x force in the x-direction.
     * @param y force in the y-direction.
     * @param z force in the z-direction.
     */
    void setOldF(double x, double y, double z);


    void setParallelNeighbours(std::vector<std::shared_ptr<Particle>> pointers_parallel);

    void setDiagonalNeighbours(std::vector<std::shared_ptr<Particle>> pointers_diagonal);

    void setStiffness(double val);

    void setBondLength(double val);

    void setId(int val);


    /**
     * @brief Sets the value of markedForMirroring to true
     *
     * @param other
     * @return
     */
    void markForMirroring();

    /**
     * @brief Sets the value of markedForMirroring to true
     *
     * @param other
     * @return
     */
    void unmarkForMirroring();

    /**
     * @brief Sets the value of markedForDeleting to true
     */
    void markForDeleting();

    /**
     * @brief Returns the value of markedForDeleting
     * @return bool
     */
    bool isMarkedForDeleting() const;

    bool operator==(const Particle &other) const;

    std::string toString() const;

     /**
     *@brief Checks for inequality between two Particle objects.
     *
     * @param other The Particle object to compare with.
     * @return true if the Particle objects are not equal, false otherwise.
     */
    bool operator!=(const Particle& other) const;

 
};

std::ostream &operator<<(std::ostream &stream, Particle &p);

 
