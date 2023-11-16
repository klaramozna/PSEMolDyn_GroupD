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
* With the help of GitHub actions, we now build and test our code with every pull request or push to main. 
* We make sure our code compiles and passes all address sanitizer checks. 
* We also run our tests with ctest

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
* We created a new class ```CuboidGenerator``` that inherits from the class ```ParticleGenerator```. We made the ```generateParticles``` function virtual as different types of particle generators will probably be implemented in the future and run-time polymorphism might be needed.
* We implemented a new method for force calculation, which computes the Lennard-Jones force between two molecules. The integration of this method to our project was convenient thanks to the parent class ```ForceCalculation``` which was required from worksheet 1 inorder to improve readability and easy integration of new force types. Another thing we did to improve the efficiency of this method is that we cached repeated computation when translating the mathematical formula in code.
* We changed our implementation of force calculation from using a nested for loop to only iterating over distinct pairs of particles. We also applied Newton's third law to avoid unnecessary calculations. Both of these changed should, in theory, make our code faster, since we reduced the amount of iterations as well has halved the amount of force calculations. However, this improvement wasn't reflected in our measurements. We tested the executions time of the calculateF function with multiple different particle containers. One with 1000 particles, one with 100 particles and one with 10 particles. In all of those cases, our old implementation with a nested loop was consistently faster (~30% lower execution time). We suspect this is due to an additional loop that is needed in our new implementation to set the old force correctly.
* To simplify the code in the ```Simulation``` class. We outsourced the iteration over both single particles and pairs of particles to the ```ParticleContainer``` class. We simply call our ```applyToAll``` and ```applyToPairs``` functions, passing the functions with calculations as lambda expressions.
* We performed the 2D Simulation of the collision of the two bodies with the given parameters in the worksheet. We also provided a video of our result simulation:

https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/7ae15dff-bda3-4fdf-904e-31e34f2324f5

  

* Benchmark?
  
# Misc #
## Using github Issues Feature to improve our code ##
* During our last meeting, where we discussed Worksheet 1, we actively took notes to thoroughly evaluate our work. We recognized the importance of refining our code and addressing specific areas of improvement. To streamline our collaboration and track the tasks efficiently, we utilized the GitHub issues feature. This approach allowed us to incorporate the valuable feedback we received, breaking down the feedback into smaller tasks that we could address.   
<img src=issues.png>
