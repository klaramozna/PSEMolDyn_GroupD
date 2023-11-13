/*
 * CL.h
 *
 *  Created on: 9.11.2023
 *      Author: RayenManai
 */

#pragma once

/* Boost */
#include <boost/program_options.hpp>
#include <filesystem>

namespace po = boost::program_options;


class CL{ 

private:
     /**
     * Allowed Options
     */
   po::options_description desc{"Allowed options"};

public:

/**
     * @brief checks if a double value is positive or not (used to handle incorrect user input)
     * @param value the value to check
     * @param option_name specify which option
*/
void validate_positive(const double& value, const std::string& option_name);

 /**
     * @brief checks if an int value is in [0, 6] (otherwise incorrect log_level)
     * @param value the value to check
     * @param option_name specify which option
*/
void validate_range(const int& value, const std::string& option_name);

 /**
     * @brief produces the help message as a string
     * @param desc the allowed options description
     * @return the help message as a string
*/
std::string produce_help_message(const po::options_description &desc);

 /**
    * @brief parses the arguments provided by the user and configures simulation parameters
    * @param argc The number of command line arguments.
    * @param argsv An array containing the command line arguments.
    * @param end_time Reference to a double variable where the end time of the simulation will be stored.
    * @param delta_t Reference to a double variable where the time step between iterations will be stored.
    * @param log_level Reference to an integer variable where the log level will be stored
    *                  (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off).
    * @param input_path Reference to a string variable where the input file path will be stored.
    * @return int the status of the process (!= 0 if an error occured)
    * 
    * @throws std::invalid_argument If invalid or incomplete arguments are provided.
     
*/
int parse_arguments(int argc, char *argsv[], double& end_time, double& delta_t, int& log_level, std::string& input_path);

};