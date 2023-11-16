/*
 * CL.h
 *
 *  Created on: 9.11.2023
 *      Author: RayenManai
 */

#include "CL.h"
#include<iostream>

/* Logging*/
#include "Logger.h"



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

int CL::parse_arguments(int argc, char *argsv[], double& end_time, double& delta_t, int& log_level, std::string& input_path, std::string& input_mode, std::string& force, double& averageVelo, bool& testing){
    desc.add_options()
        ("help,h", "produce help message")
        ("input_mode,m", po::value<std::string>(&input_mode)->default_value("cuboid"), "Select between modes of input (cuboid or particle)")
        ("input_path,p", po::value<std::string>(), "the path to the input file")
        ("t_end,e", po::value<double>(&end_time)->default_value(5)->notifier([this](const double& value) {
            this->validate_positive(value, "t_end");
        }), "end time of simulation")
        ("delta_t,s", po::value<double>(&delta_t)->default_value(0.0002)->notifier([this](const double& value) {
            this->validate_positive(value, "delta_t");
        }), "step size between iterations")
        ("velocity, v", po::value<double>(&averageVelo)->default_value(0.1), "average Brownian motion velocity")
        ("force,f", po::value<std::string>(&force)->default_value("lennard"), "Select between force calculation engines (lennard or grav)")
        ("testing,t", po::bool_switch(&testing)->default_value(false), "enable testing mode")
        ("log_level,l", po::value<int>(&log_level)->default_value(2)->notifier([this](const int& value) {
            this->validate_range(value, "log_level");
        }), "sets the log level (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)")
        ;

    Logger::console->info("Hello from MolSim for PSE!");

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
    if (vm.count("input_path") && std::filesystem::exists(vm["input_path"].as<std::string>())) {
        input_path = vm["input_path"].as<std::string>();
        Logger::console->info("Input path: {}", input_path);
    } else {
        Logger::err_logger->error("Input file not specified or invalid.");
        Logger::console->info("{}", produce_help_message(desc));
        return 1;
    }

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

    if (vm.count("force")) {
        std::string input_string = vm["force"].as<std::string>();
        if (input_string == "lennard" || input_string == "grav") {
            force = input_string;
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

    return 0;
}