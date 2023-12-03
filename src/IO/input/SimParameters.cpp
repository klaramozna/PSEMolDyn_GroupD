/*
 * simParameters.cpp
 *
 *  Created on: 24.11.2023
 *      Author: RayenManai
 */

#include <string>
#include"SimParameters.h"

    // Constructor to initialize the parameters
SimParameters::SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val, const double cutoffRadius_val, const std::array<double,3>& boxSize_val, const std::array<std::string, 6>& boundaryBehavior_val){
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
                    cutoffRadius = cutoffRadius_val;
                    boxSize = boxSize_val;
                    boundaryBehavior = boundaryBehavior_val;
                  }

SimParameters::SimParameters(double end_time_val, double delta_t_val, double averageVelo_val,
                  bool testing_val, int log_level_val,
                  const std::string& input_path_val, const std::string& input_mode_val,
                  const std::string& force_val, const double sigma_val, const double epsilon_val, const std::string& base_name_val){
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
         base_name == other.getBaseName();
}



