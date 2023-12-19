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
bool log_level_set = false;

void init(int log_level) {
    spdlog::set_level(spdlog::level::level_enum(log_level));
}

void set_log_level_set() {
    log_level_set = true;
}

bool is_log_level_set() {
    return log_level_set;
}
}