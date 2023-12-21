# MolSim

Bachelor Practical course:  
`PSE Molecular Dynamics:` Developing a Molecular Dynamics Simulation  



### Team Members

   - Rodrigo Felix Forno
   - Klára Možná
   - Rayen Manai

### Table of Contents

- [MolSim](#molsim)
    - [Team Members](#team-members)
    - [Table of Contents](#table-of-contents)
    - [Introduction](#introduction)
    - [Features](#features)
    - [Requirements](#requirements)
    - [Getting Started](#getting-started)
    - [Usage](#usage)
      - [Command Line Usage:](#command-line-usage)
        - [Optional arguments:](#optional-arguments)
    - [Checkpoints:](#checkpoints)
      - [Tests:](#tests)
    - [Documentation:](#documentation)
        - [Build Doxygen Documentation](#build-doxygen-documentation)

<a name="introduction"></a>
### Introduction



<a name="features"></a>
### Features

    Particle Representation: Implementation of particle representations.
    Force Calculation: Algorithms for computing inter-particle forces.
    Output and Visualization: Output formats and tools for visualizing simulation results.

<a name="requirements"></a>
### Requirements

  - C++ compiler: ```sudo apt-get install g++```
  - Cmake: ```sudo apt-get install cmake```
  - Make: ```sudo apt-get install make```
  - Xerces-C library: ```sudo apt-get install libxerces-c-dev```
  - Boost program options: ```sudo apt-get install libboost-program-options-dev```
  - Boost test environment: ```sudo apt-get install libboost-test-dev ```
  - Pkg-config: ``` sudo apt-get install pkg-config ```

<a name="gettingStarted"></a>
### Getting Started


1. clone the repository: ```git clone https://github.com/klaramozna/PSEMolDyn_GroupD```  
2. Navigate to the Project Directory: ```cd PSEMolDyn_GroupD```  
3. Create Build Directory and navigate to it: ```mkdir build && cd build```  
4. Configure with CMake: ```cmake ..```  
5. Compile the Project: ```make```  

<a name="usage"></a>
### Usage

#### Command Line Usage:
run the program with: ```./src/MolSim -p <input_file_path>```  

##### Optional arguments:
- ```-h , --help```: produces help message
- ```-e, --t_end```: specifies end time of simulation(default: 1000)
- ```-s, --delta_t```: specifies the step size between iterations(default: 0.014)
- ```-l, --log_level```: specifies the log level [0: trace, 1: debug, 2: info, 3: warning, 4: error, 5: critical, 6: off] (default: 2)
- ```-f,--force```: Select between force calculation engines lennard or grav (default: lennard)
- ```-t, --testing```: enable testing mode (to benchmark)
- ```-m,--input_mode```:   Select between modes of input cuboid or particle (default: cuboid)

### Checkpoints:
Checkpoints are crucial in molecular dynamics, like simulating a falling drop in liquid. They save system states, aiding equilibration and data integrity.
- ```-c , --store_checkpoint```: Enter checkpoint filename to store
- ```-x , --load_checkpoint```: Enter checkpoint filename to load

#### Tests:
This project is well-tested using Google Test.  
To run the tests locally switch to the build directory and run ```ctest```  
Per default running ```cmake ..``` will fetch the google test libray and compile the tests (which results in longer building times), if you want to not compile the tests you can run ```cmake -DBUILD_GTESTS=OFF ..```
<a name="documentation"></a>

### Documentation:
This project is well-documented using Doxygen.   
The documentation is at the following Link: [Project Documentation](https://klaramozna.github.io/PSEMolDyn_GroupD/)  
To generate it locally, follow these steps:  

##### Build Doxygen Documentation 
- Create Build Directory and navigate to it: ```mkdir build && cd build```  
- Configure with CMake and enable the Doxygen documentation generation option: ```cmake -DBUILD_DOXYGEN=ON ..```
- Compile the Project: ```make doc_doxygen``` 


