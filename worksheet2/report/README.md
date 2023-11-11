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
* We made ourselves familiar with ```spdlog``` .It is a high-performance C++ logging library and offers a powerful API for logging messages at various levels. The library is header-only, making it easy to integrate into C++ projects, and supports logging to multiple sinks, such as console and files. Furthemore it is designed to be thread-safe. 
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

* To integrate the latest version of spdlog into our project without relying on system-wide installed libraries and without imposing additional manual installation steps for users, we employed the ```FetchContent``` module provided by CMake. This approach allows us to include spdlog directly from its official repository during the CMake configuration process. By specifying the repository URL and tag details in our CMakeLists.txt file, the necessary components of spdlog will be automatically downloaded and included in our project.
```cmake
include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
```
* 

* Users can dynamically choose the log level through convenient command-line options without the need to manually edit any source files.   
Run the program with``` --log_level <value in [0, 6]>``` or ``` -l <value in [0, 6]>```  
where : ```log level (0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off)```

## Task 4 ”Collision of two bodies” ##
* 
  
# Misc #
## Using github Issues Feature to improve our code ##
* During our last meeting, where we discussed Worksheet 1, we actively took notes to thoroughly evaluate our work. We recognized the importance of refining our code and addressing specific areas of improvement. To streamline our collaboration and track the tasks efficiently, we utilized the GitHub issues feature. This approach allowed us to incorporate the valuable feedback we received, breaking down the feedback into smaller tasks that we could address. 
<img src=issues.png>