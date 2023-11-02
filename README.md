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
    - [Documentation](#documentation)
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
run the program with: ```./MolSim -p <input_file_path>```  

##### Optional arguments:
- ```-h , --help```: produces help message
- ```-e, --t_end```: specifies end time of simulation(default: 1000)
- ```-s, --delta_t```: specifies the step size between iterations(default: 0.014)


<a name="documentation"></a>
### Documentation
This project is well-documented using Doxygen.   
The documentation is at the following Link: [Project Documentation](https://klaramozna.github.io/PSEMolDyn_GroupD/)  
To generate it locally, follow these steps:  

##### Build Doxygen Documentation 
- Create Build Directory and navigate to it: ```mkdir build && cd build```  
- Configure with CMake and enable the Doxygen documentation generation option: ```cmake -DBUILD_DOXYGEN=ON ..```
- Compile the Project: ```make doc_doxygen``` 


