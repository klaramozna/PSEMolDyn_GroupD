/*
 * Logger.h
 *
 *  Created on: 11.11.2023
 *      Author: RayenManai
 */
#pragma once

#include<memory>

/* Logging*/
#include <spdlog/spdlog.h>
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Logger {

 /**
  * logger for general infos
  */
extern std::shared_ptr<spdlog::logger> console;    
/**
  * logger for displaying errors
  */
extern std::shared_ptr<spdlog::logger> err_logger;  

/**
  * file logger
*/
extern std::shared_ptr<spdlog::logger> file_logger;


/**
     * @brief sets the log level
     * @param log_level value in [0, 6], (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)
*/
void init(int log_level);



}