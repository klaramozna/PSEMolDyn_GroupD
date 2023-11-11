# Group D #
Members:
* Rodrigo Felix Forno
* Klára Možná
* Rayen Manai

# Code #
* Link:     https://github.com/klaramozna/PSEMolDyn_GroupD
* Branch:   main
* Revision: 
* Compiler: g++ 11.4.0
* Documentation: https://klaramozna.github.io/PSEMolDyn_GroupD/


# Report #
## Task 1 ”Unit tests” ##
* 

## Task 2 ”Continuous Integration” ##
* 

## Task 3 ”Logging” ##
* We made ourselves familiar with ```spdlog```. It is a high-performance, C++ logging library and offers a powerful API for logging messages at various levels. The library is header-only, making it easy to integrate into C++ projects, and supports logging to multiple sinks, such as console and files. Furthemore it is designed to be thread-safe.     
```spdlog``` provides different log levels to categorize and prioritize log messages based on their severity. The available log levels, in increasing order of severity, are `trace`, `debug`, `info`, `warn`, `error`, `critical`, and `off`. Developers can use these levels to control which messages get logged. For example, setting the log level to `info` will log messages of `info` severity and higher (e.g., `warn`, `error`, `critical`). This flexibility helps tailor the logging output to specific needs.
* Both log functions and log macros serve similar purposes but they have some differences.
#### Log Functions ####
- They are regular C++ functions provided by the spdlog library, for example: 
```C++
spdlog::info("This is an informational message");
spdlog::warn("This is a warning message");
spdlog::error("This is an error message");
```
#### Log Macros ####
- They are preprocessor macros that simplify the logging process, for example:
```C++
SPDLOG_INFO("This is an informational message");
SPDLOG_WARN("This is a warning message");
SPDLOG_ERROR("This is an error message");
```
* In designing our logging system, we chose log functions over log macros. Log functions offer a more structured and type-safe approach to logging. They provide flexibility in handling log messages, allowing for dynamic log levels. Functions also align with modern C++ practices, offering better integration with namespaces and encapsulation. 

* To integrate the latest version of spdlog into our project without relying on system-wide installed libraries and without imposing additional manual installation steps for users, we leveraged the convenience of a ```header-only``` library. A header-only library, such as spdlog, delivers C++ functionality through included header files, eliminating the need for separate compilation steps in project integration.  
We downloaded the latest header files directly from the spdlog repository and included them in our project in the ```libs``` folder. It's straight forward process. No need to deal with additional CMake commands or package management.
* In structuring the loggers, we established a modular approach encapsulated within the ```"Logger" namespace```. Three loggers were defined, each serving distinct purposes: a ```console``` logger for standard output(Info), an ```error``` logger for standard error, and a ```file``` logger recording logs to a specified file path. We implemented also an `init` function that enables dynamic adjustment of the logging level based on the provided parameter(if provided by user), enhancing adaptability to different debugging or logging scenarios. This design facilitates an organized logging system within the codebase, replacing the use of ```std::cout``` with efficient ```spdlog```  instructions.  
Whenever we need to log in our code we just need to adress the suitable logger from the created namespace Logger.

* Users can dynamically choose the log level through convenient command-line options without the need to manually edit any source files.   
Run the program with``` --log_level <value in [0, 6]>``` or ``` -l <value in [0, 6]>```  
where : ```log level (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)```

## Task 4 ”Collision of two bodies” ##
* 
  
# Misc #
## Using github Issues Feature to improve our code ##
* During our last meeting, where we discussed Worksheet 1, we actively took notes to thoroughly evaluate our work. We recognized the importance of refining our code and addressing specific areas of improvement. To streamline our collaboration and track the tasks efficiently, we utilized the GitHub issues feature. This approach allowed us to incorporate the valuable feedback we received, breaking down the feedback into smaller tasks that we could address.   
<img src=issues.png>