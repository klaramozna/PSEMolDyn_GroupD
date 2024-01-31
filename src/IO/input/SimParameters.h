/*
 * SimParameters.h
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#pragma once

#include <string>
#include <array>
#include "utils/ParallelizationSpec.h"

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
     * @param write_frequency frequency of creating ouptput files
     * @param cutoffRadius_val base name for the output files
     * @param  boxSize_val the domain size
     * @param  boundaryBehavior_val behavior of boundaries
     * @param initTemp Initial temperature of molecules.
     * @param targetTemp Target temperature of molecules.
     * @param maxChange Maximum temperature change per iteration.
     * @param cycleLength The number of cycles in which thermostat is periodically applied.
     * @param gravity_factor_val the gravity factor g_grav which adds a gravitational force G
     * @param isMembrane_val boolean true when membrane is present 
     */
    SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const int write_frequency, const double cutoffRadius_val, const std::array<double,3>& boxSize_val, const std::array<std::string, 6>& boundaryBehavior_val, double initTemp, double targetTemp, double maxChange, int cycleLength, const std::string& thermostatType, bool brownianMotion, std::array<double,3>  gravity_factor_val  = {0, 0, 0}, bool isMembrane_val= false, double hardcoded_force_end_time =150, std::array<double,3> hardcoded_pull_factors = {0, 0, 0});

    SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const int write_frequency);
    SimParameters() = default;

    void print();

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
    int getWriteFrequency () const {return write_frequency;}
    double getCutoffRadius() const { return cutoffRadius; }
    std::array<double,3> getBoxSize() const {return boxSize;}
    std::array<std::string,6> getBoundaryBehavior() const {return boundaryBehavior;}
    std::string getStoreCheckpoint() const { return store_checkpoint_path ;}
    std::string getloadCheckpoint() const { return load_checkpoint_path ;}
    double getInitTemperature()const {return  initTemperature;}
    double getThermostatCycleLength()const{return  thermostatCycleLength;}
    double getTargetTemperature()const{return targetTemperature;}
    double getMaxTemperatureChange()const{return maxTemperatureChange;}
    std::array<double,3>  getGravityFactor() const {return gravity_factor;}
    std::string getThermostatType() const {return thermostatType;}
    bool getBrownianMotion() const {return brownianMotion;}
    int getDim(){return dim;};
    ParallelizationSpec& getParallelizationSpec() { return parallelizationSpec; }
    SchedulerType getSchedulerType() const {return schedulerType;};
    bool isMembrane() const {return is_Membrane;}
    double getHardcodedForceEndTime() const {return hardcoded_force_end_time;}
    std::array<double,3>  getHardcodedPullFactors() const {return hardcoded_pull_factors;}

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
    void setWriteFrequency (const int val) {write_frequency = val;}
    void setCutoffRadius(const double val) { cutoffRadius = val; }
    void setBoxSize(const std::array<double,3>& val)  {boxSize = val;}
    void setBoundaryBehavior(const std::array<std::string, 6>& val) { boundaryBehavior = val;}
    void setStoreCheckpoint(const std::string& val) { store_checkpoint_path = val; }
    void setLoadCheckpoint(const std::string& val) { load_checkpoint_path = val; }
    void setInitTemperature(double val){initTemperature = val;}
    void setThermostatCycleLength(int val){thermostatCycleLength = val;}
    void setTargetTemperature(double val){targetTemperature = val;}
    void setMaxTemperatureChange(double val){maxTemperatureChange = val;}
    void setGravityFactor (std::array<double,3>  val) {gravity_factor = val;}
    void setThermostatType (const std::string& thermostatType_val){thermostatType = thermostatType_val;}
    void setBrownianMotion(bool val){brownianMotion = val;}
    void setDimension(int val){dim = val;};
    void setSchedulerType(SchedulerType val) {schedulerType = val;};
    void setIsMembrane (bool val) {is_Membrane = val;}
    void setHardcodedForceEndTime(double val) {hardcoded_force_end_time = val;}
    bool operator==(const SimParameters &other) const;
    void setHardcodedPullFactors(std::array<double,3>  val) { hardcoded_pull_factors = val;}

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
    * @brief write frequency
    */
    int write_frequency = 10;
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

    /**
    * @brief checkpoint path to store
    */
    std::string store_checkpoint_path;

    /**
    * @brief checkpoint path to load from
    */
    std::string load_checkpoint_path;

    /**
     * @brief Temperature that the thermostat can be initialized with.
     */
    double initTemperature;

    /**
     * @brief The number of iterations, per which the thermostat is applied.
     */
    int thermostatCycleLength;

    /**
     * @brief Target temperature of the system.
     */
    double targetTemperature;

    /**
     * @brief Maximum change of temperature per iteration.
     */
    double maxTemperatureChange;

    /**
     * @brief g_grav which adds a gravitational force G 
     */
    std::array<double,3>  gravity_factor = {0, 0, 0};

    /**
     * @brief none, simple or gradual depending on the type of the thermostat.
     */
    std::string thermostatType;

    /**
     * @brief True - brownian motion should be applied, False - not applied
     */
    bool brownianMotion;

    /**
     * @brief dimension of the simulation (2 or 3)
     */
     int dim;
    /**
     * @brief membrane present or not
     */
    bool is_Membrane = false;
    /**
     * @brief end time of hard coded pull force
     */
    double hardcoded_force_end_time;

     /** Parameters relevant for the Parallelization Strategy **\

     /**
      * @brief parallelization strategy: none, subdomaining or cell-list
      */
     ParallelizationSpec parallelizationSpec;

     /**
      * @brief scheduling type: static, dynamic or guided
      */
     SchedulerType schedulerType;
    /**
     * @brief pull force factors
     */
    std::array<double,3> hardcoded_pull_factors = {0, 0, 0};
};
