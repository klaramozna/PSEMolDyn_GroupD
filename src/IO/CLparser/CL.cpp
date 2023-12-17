/*
 * CL.h
 *
 *  Created on: 9.11.2023
 *      Author: RayenManai
 */

#include "CL.h"
#include<iostream>

/* Logging*/
#include "IO/Logger.h"

CL::CL() {
    desc.add_options()
        ("help,h", "produce help message")
        ("input_mode,m", po::value<std::string>(&input_mode), "Select between modes of input (cuboid or particle)")
        ("input_path,p", po::value<std::string>(&input_path), "the path to the input file")
        ("t_end,e", po::value<double>(&end_time)->default_value(5)->notifier([this](const double& value) {
            this->validate_positive(value, "t_end");
        }), "end time of simulation")
        ("delta_t,s", po::value<double>(&delta_t)->default_value(0.0002)->notifier([this](const double& value) {
            this->validate_positive(value, "delta_t");
        }), "step size between iterations")
        ("velocity,v", po::value<double>(&averageVelo)->default_value(0.1), "average Brownian motion velocity")
        ("force,f", po::value<std::string>(&force)->default_value("lennard"), "Select between force calculation engines (lennard or grav or MixingRuleLennardJones)")
        ("gravity,g", po::value<double>(&gravity_factor)->default_value(0), "Select a gravity factor value")
        ("testing,t", po::bool_switch(&testing)->default_value(false), "enable testing mode for benchmarking")
        ("log_level,l", po::value<int>(&log_level)->default_value(2)->notifier([this](const int& value) {
            this->validate_range(value, "log_level");
        }), "sets the log level (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)")
        ("write_frequency,w", po::value<int>(&write_frequency)->default_value(100), "Select the write frequency (for output files generation)")
        ("store_checkpoint,c", po::value<std::string>(&store_checkpoint_path), "Enter checkpoint filename to store")
        ("load_checkpoint,x", po::value<std::string>(&load_checkpoint_path), "Enter checkpoint filename to load")
        ;
}

void CL::validate_positive(const double& value, const std::string& option_name) {
    if (value <= 0) {
        throw po::validation_error(po::validation_error::invalid_option_value,
            option_name);
    }
}

void CL::validate_range(const int& value, const std::string& option_name) {
    if (value < 0 || value > 6) {
        throw po::validation_error(po::validation_error::invalid_option_value,
            option_name);
    }
}

std::string CL::produce_help_message(const po::options_description &desc){
    std::ostringstream oss;
    oss << desc;
    return oss.str();
}

bool hasXMLExtension(const std::string& input_path) {
    std::string lowercasePath = input_path;
    std::transform(lowercasePath.begin(), lowercasePath.end(), lowercasePath.begin(), ::tolower);
    return (lowercasePath.length() >= 4 && lowercasePath.substr(lowercasePath.length() - 4) == ".xml");
}

int CL::parse_input_path_and_mode_and_log(int argc, char *argsv[], SimParameters& simParameters) {
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argsv, desc), vm);
        po::notify(vm);
    }   catch (po::error &e) {
        Logger::err_logger->error("Erroneous program call!");
        Logger::err_logger->error("{}",e.what());
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }

    if (vm.count("help")) {
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }

    if (vm.count("input_path") && std::filesystem::exists(vm["input_path"].as<std::string>())) {
        input_path = vm["input_path"].as<std::string>();
        if (hasXMLExtension(input_path)){
            input_mode = "xml";
            simParameters.setInputMode("xml");
            simParameters.setInputPath(input_path);
            Logger::console->debug("Reading from XML: {}", input_path);
        }
    } else {
        Logger::err_logger->error("Input file not specified or invalid.");
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }
    if (input_mode !="xml"){
        if (vm.count("input_mode")) {
            std::string input_string = vm["input_mode"].as<std::string>();
            if (input_string == "cuboid" || input_string == "particle") {
                input_mode = input_string;
            } else {
                Logger::err_logger->error("Input mode is invalid");
                Logger::console->info("{}", produce_help_message(desc));
                return 1;
            }
        } else {
            Logger::err_logger->error("Input mode is not specified");
            Logger::console->info("{}", produce_help_message(desc));
            return 1;
        }
    }
    simParameters.setInputMode(input_mode);
    simParameters.setInputPath(input_path);
    simParameters.setLogLevel(log_level);
    Logger::init(log_level);
    Logger::set_log_level_set();
    return 0;
}


int CL::parse_arguments(int argc, char *argsv[], SimParameters& simParameters){
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argsv, desc), vm);
        po::notify(vm);
        Logger::init(log_level);
    }

    //deal with any erroneous program(incorrect user input)
    catch (po::error &e) {
        Logger::err_logger->error("Erroneous program call!");
        Logger::err_logger->error("{}",e.what());
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }

    if (vm.count("help")) {
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }

    if (vm.count("store_checkpoint")){
        Logger::console->debug("Storing Checkpoint to {}", store_checkpoint_path);
        simParameters.setStoreCheckpoint(store_checkpoint_path);
    }

    if (vm.count("load_checkpoint")){
        Logger::console->debug("Loading Checkpoint from {}", load_checkpoint_path);
        simParameters.setLoadCheckpoint(load_checkpoint_path);
    }
    if (vm.count("force")) {
        std::string input_string = vm["force"].as<std::string>();
        if (input_string == "lennard" || input_string == "grav"|| input_string == "MixingRuleLennardJones") {
            force = input_string;
            simParameters.setForce(force);
        } else {
            Logger::err_logger->error("Force calculation is invalid");
            Logger::console->info("{}", produce_help_message(desc));
            return 1;
        }
    } else {
        Logger::err_logger->error("Force calculation is not specified");
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }
    if (vm.count("velocity")) {
        simParameters.setAverageVelo(averageVelo);
    }
    if (vm.count("delta_t")){
        simParameters.setDeltaT(delta_t);
    }
    if (vm.count("t_end")){
        simParameters.setEndTime(end_time);
    }
    if (vm.count("testing")){
        simParameters.setTesting(testing);
    }
    if (vm.count("write_frequency")){
        simParameters.setWriteFrequency(write_frequency);
    }
    if (vm.count("gravity")){
        simParameters.setGravityFactor(gravity_factor);
    }
    return 0;
}