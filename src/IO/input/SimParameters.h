/*
 * SimParameters.h
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#pragma once

#include <string>
#include <array>

/**
 * @brief Represents simulation parameters.
 *
 * This class encapsulates simulation parameters and provides methods
 * to access and modify these parameters.
 */
class SimParameters {
public:
    /**
     * @brief Constructor to initialize simulation parameters.
     *
     * @param end_time_val The end time.
     * @param delta_t_val The step size.
     * @param averageVelo_val The average velocity.
     * @param testing_val Testing mode for benchmarking (true/false).
     * @param log_level_val The log level.
     * @param input_path_val The input path.
     * @param input_mode_val The input mode.
     * @param force_val The force type.
     * @param sigma_val sigma value
     * @param epsilon_val epsilon value 
     * @param base_name_val base name for the output files
     * @param cutoffRadius_val base name for the output files
     * @param  boxSize_val the domain size
     * @param  boundaryBehavior_val behavior of boundaries
     */
    SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const double cutoffRadius_val, const std::array<double,3>& boxSize_val, const std::array<std::string, 6>& boundaryBehavior_val);

    SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val);
    SimParameters() = default;


    // Getters for retrieving parameter values
    constexpr double getStartTime() const { return start_time; }
    double getEndTime() const { return end_time; }
    double getDeltaT() const { return delta_t; }
    double getAverageVelo() const { return averageVelo; }
    bool isTesting() const { return testing; }
    int getLogLevel() const { return log_level; }
    std::string getInputPath() const { return input_path; }
    std::string getInputMode() const { return input_mode; }
    std::string getForce() const { return force; }
    double getSigma() const {return sigma;}
    double getEpsilon() const {return epsilon;}
    std::string getBaseName() const { return base_name; }
    double getCutoffRadius() const { return cutoffRadius; }
    std::array<double,3> getBoxSize() const {return boxSize;}
    std::array<std::string,6> getBoundaryBehavior() const {return boundaryBehavior;}   

    // Setters for modifying parameter values
    void setEndTime(double val) { end_time = val; }
    void setDeltaT(double val) { delta_t = val; }
    void setAverageVelo(double val) { averageVelo = val; }
    void setTesting(bool val) { testing = val; }
    void setLogLevel(int val) { log_level = val; }
    void setInputPath(const std::string& val) { input_path = val; }
    void setInputMode(const std::string& val) { input_mode = val; }
    void setForce(const std::string& val) { force = val; }
    void setSigma(const double val) {sigma = val;}
    void setEpsilon(const double val) {epsilon = val;}
    void setBaseName(const std::string val) {base_name = val;}
    void setCutoffRadius(const double val) { cutoffRadius = val; }
    void setBoxSize(const std::array<double,3>& val)  {boxSize = val;}
    void setBoundaryBehavior(const std::array<std::string, 6>& val) { boundaryBehavior = val;} 

    bool operator==(const SimParameters &other) const;


private:
    /**
     * @brief start time of the simulation = 0
     */
    static constexpr double start_time = 0.0;
    /**
     * @brief epsilon value
     */
    double epsilon = 5.0;
    /**
     * @brief sigma value
     */
    double sigma = 1.0;
    
    /**
     * @brief The end time.
     */
    double end_time;

    /**
     * @brief The step size.
     */
    double delta_t;

    /**
     * @brief The average velocity.
     */
    double averageVelo;

    /**
     * @brief Testing mode (true/false).
     */
    bool testing;

    /**
     * @brief The log level.
     */
    int log_level;

    /**
     * @brief The input path.
     */
    std::string input_path;

    /**
     * @brief The input mode.
     */
    std::string input_mode;

    /**
     * @brief The force type.
     */
    std::string force;
     /**
     * @brief output file base name
     */
    std::string base_name = "MD_vtk";
    /**
     * @brief cutoff radius
     */
    double cutoffRadius;
    /**
     * @brief domain size 
     */
    std::array<double,3> boxSize;
    /**
     * @brief behaviour of the 6 boundaries in this order (Front, Back, Top, Right, Bottom, Left) 
     */
    std::array<std::string, 6> boundaryBehavior;



};
