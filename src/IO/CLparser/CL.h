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

#include "./../input/SimParameters.h"

namespace po = boost::program_options;


class CL{ 

private:
     /**
     * Allowed Options
     */
    po::options_description desc{"Allowed options"};

    po::variables_map vm;
    /*
    * sim arguments
    **/
    std::string input_path;
    std::string input_mode;
    double end_time;
    double delta_t;
    double averageVelo;
    bool testing;
    int log_level;
    int write_frequency;
    double gravity_factor;
    std::string force;
    std::string store_checkpoint_path;
    std::string load_checkpoint_path;

public:
     CL ();
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
    * @param simParameters instance holding the simulation parameters
    * @throws std::invalid_argument If invalid or incomplete arguments are provided.
     
*/
int parse_arguments(int argc, char *argsv[], SimParameters& simParameters);

 /**
    * @brief parses the input path and mode
    * @param argc The number of command line arguments.
    * @param argsv An array containing the command line arguments.
    * @param simParameters instance holding the simulation parameters
    * @throws std::invalid_argument If invalid or incomplete arguments are provided.
     
*/
int parse_input_path_and_mode_and_log(int argc, char *argsv[], SimParameters& simParameters);

};