/*
 * simParameters.cpp
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#include <string>
#include "SimParameters.h"
#include "../Logger.h"
#include "utils/ParallelizationSpec.h"

// Constructor to initialize the parameters
SimParameters::SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                             bool testing_val, int log_level_val,
                             const std::string& input_path_val, const std::string& input_mode_val,
                             const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const int write_frequency_val, const double cutoffRadius_val, const std::array<double,3>& boxSize_val, const std::array<std::string, 6>& boundaryBehavior_val, double initTemp, double targetTemp, double maxChange, int cycleLength, const std::string& thermostatType, bool brownianMotion, std::array<double,3> gravity_factor_val, bool isMembrane_val, double hardcoded_force_end_time , std::array<double,3> hardcoded_pull_factors){
    end_time =end_time_val;
    delta_t = delta_t_val;
    averageVelo = averageVelo_val;
    testing=testing_val;
    log_level =log_level_val;
    input_path= input_path_val;
    input_mode = input_mode_val;
    force = force_val;
    sigma=sigma_val;
    epsilon = epsilon_val;
    base_name = base_name_val;
    write_frequency = write_frequency_val;
    cutoffRadius = cutoffRadius_val;
    boxSize = boxSize_val;
    boundaryBehavior = boundaryBehavior_val;
    initTemperature = initTemp;
    targetTemperature = targetTemp;
    maxTemperatureChange = maxChange;
    thermostatCycleLength = cycleLength;
    gravity_factor = gravity_factor_val;
    this->thermostatType = thermostatType;
    this->brownianMotion = brownianMotion;
    this->parallelizationSpec = ParallelizationSpec();
    this->is_Membrane = isMembrane_val;
    this->hardcoded_force_end_time = hardcoded_force_end_time;
    this->hardcoded_pull_factors = hardcoded_pull_factors;
}

SimParameters::SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                             bool testing_val, int log_level_val,
                             const std::string& input_path_val, const std::string& input_mode_val,
                             const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const int write_frequency_val ){
    end_time =end_time_val;
    delta_t = delta_t_val;
    averageVelo = averageVelo_val;
    testing=testing_val;
    log_level =log_level_val;
    input_path= input_path_val;
    input_mode = input_mode_val;
    force = force_val;
    sigma=sigma_val;
    epsilon = epsilon_val;
    base_name = base_name_val;
    write_frequency = write_frequency_val;
    is_Membrane = false;
}

bool SimParameters::operator==(const SimParameters &other) const {
    return epsilon == other.getEpsilon() &&
           sigma == other.getSigma() &&
           end_time == other.getEndTime() &&
           delta_t == other.getDeltaT() &&
           averageVelo == other.getAverageVelo() &&
           testing == other.isTesting() &&
           log_level == other.getLogLevel() &&
           input_mode == other.getInputMode() &&
           input_path == other.getInputPath() &&
           force == other.getForce() &&
           base_name == other.getBaseName() &&
           write_frequency == other.getWriteFrequency() &&
           initTemperature == other.getInitTemperature() &&
           targetTemperature == other.getTargetTemperature() &&
           maxTemperatureChange == other.getMaxTemperatureChange() &&
           thermostatCycleLength == other.getThermostatCycleLength() &&
           dim == other.dim &&
           is_Membrane == other.is_Membrane;
}

void SimParameters::print(){
    Logger::console->debug("End Time: {}", end_time);
    Logger::console->debug("Delta_t: {}", delta_t);
    Logger::console->debug("average Velo: {}", averageVelo);
    Logger::console->debug("Testing: {}", testing);
    Logger::console->debug("Log Level: {}", log_level);
    Logger::console->debug("input_mode: {}", input_mode);
    Logger::console->debug("input path: {}", input_path);
    Logger::console->debug("base name: {}", base_name);
    Logger::console->debug("force: {}", force);
    Logger::console->debug("Epsilon: {}", epsilon);
    Logger::console->debug("Sigma: {}", sigma);
    Logger::console->debug("write frequency: {}", write_frequency);
    Logger::console->debug("Membrane Present: {}", is_Membrane);
    if (isMembrane()){
        Logger::console->debug("Hard Coded Force end time: {}", hardcoded_force_end_time); 
    }

}

