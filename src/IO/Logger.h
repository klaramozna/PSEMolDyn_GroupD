/*
 * Logger.h
 *
 *  Created on: 11.11.2023
 *      Author: RayenManai
 */
#pragma once

#include<memory>

/* Logging*/
#include <../libs/spdlog/spdlog.h>
#include "../libs/spdlog/sinks/stdout_color_sinks.h"
#include "../libs/spdlog/sinks/basic_file_sink.h"

namespace Logger {

 /**
  *@brief logger for general infos
  */
extern std::shared_ptr<spdlog::logger> console;    
/**
  *@brief logger for displaying errors
  */
extern std::shared_ptr<spdlog::logger> err_logger;  
/**
  *@brief see if logger already set or not
*/
extern bool log_level_set;


/**
     * @brief sets the log level
     * @param log_level value in [0, 6], (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)
*/
void init(int log_level);

/**
  * @brief Sets log_level_set to true
*/
void set_log_level_set();

/**
  * @brief Checks if log_level_set is true
  * @return true if log_level_set is true, false otherwise
*/
bool is_log_level_set();

}