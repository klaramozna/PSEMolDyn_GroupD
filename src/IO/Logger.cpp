/*
 * Logger.cpp
 *
 *  Created on: 11.11.2023
 *      Author: RayenManai
 */

#include "Logger.h"


namespace Logger{


std::shared_ptr<spdlog::logger> console = spdlog::stdout_color_mt("console");    
std::shared_ptr<spdlog::logger> err_logger = spdlog::stderr_color_mt("stderr");
std::shared_ptr<spdlog::logger> file_logger = spdlog::basic_logger_mt("file_logger", "logs/logfile.txt");  

void init(int log_level) {
    spdlog::set_level(spdlog::level::level_enum(log_level));
}

}