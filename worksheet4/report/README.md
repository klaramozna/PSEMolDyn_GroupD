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
## Task 1 “Thermostats” ##
* 

## Task 2 “Simulation of the Rayleigh-Taylor instability” ##
### Periodic Boundaries: ###
  
### Gravity Force: ### 
* The gravity Force is a single particle force so it was not possible to implement it as a subclass of ForceCalculation.h like Lennard Jones. So we added a new parent class ```OneParticleForceCalculation``` and implemented ```GravityForce``` as a subclass of it, the method offered by this class will then be used in the Simulation class wrapped with the applyToAll functionality in every iteration.
* We support also this new routine through the XML input. The gravity factor is intialized with 0 so that this force has no effect if the user does not specify it. The user can overwrite this value with the XML input. The syntax is the following ``` <gravity> gravity factor value </gravity> ```

## Task 3 “Simulation of a falling drop - Liquid” ##
### Checkpointing ###
* To store checkpoints, we used the serialization functionality provided by XSD CodeSynthesis (```xsd cxx-tree --std c++11 --generate-doxygen --hxx-suffix .h --cxx-suffix .cpp  --generate-serialization ../../input/checkpointFormat.xsd ```), which generates C++ classes from an XML Schema Definition (XSD). Our approach involves defining a structured XSD format specifically for checkpoint data representation (```input/checkpointFormat.xsd```). This schema outlines the structure, elements, and data types expected within a checkpoint file (which is a sequence of particles to save the complete state of the molecules to the file, including old force, type, and so on). 
* We then utilize the generated C++ classes to serialize checkpoint data into XML format, adhering to the defined schema. This serialization ensures that the produced XML files comply with the specified format, enabling easy storage, exchange, and readability of checkpoint information.
* We added command line options to give the user the possibility to use this feature. These are explained in the repository README.
* Example Usage: to do 

## Task 4 “Performance Measurement and Profiling” ##

* using: perf
``` perf stat -o summary.txt -e cpu-cycles,cache-misses,cache-references ./src/MolSim -p ../input/<input_file> ```

## Task 5 “Tuning the sequential Performance” ##  

* 
  
# Misc #

### Pending WS3 ### 
* Falling Drop Simulation:  

