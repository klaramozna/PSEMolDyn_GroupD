# Group D #
Members:
* Rodrigo Felix Forno
* Klára Možná
* Rayen Manai

# Code #
* Link:     https://github.com/klaramozna/PSEMolDyn_GroupD
* Branch:   main
* Revision: 1075f68
* Compiler: g++ 11.4.0
* Documentation: https://klaramozna.github.io/PSEMolDyn_GroupD/
  
> **Hint:** Please have a look at our report directly on the readme on the repository (Link: https://github.com/klaramozna/PSEMolDyn_GroupD/tree/presentations%2Breports/worksheet4/report) because we have videos embedded and it looks nicer there.

# Report #

## Forewarning ##

We modified the implementation of reflecting boundaries, so that now for each boundary and particle, one "ghost" particle gets added symmetricaly to the boundary.

This has lead to the current test suite in ReflectiveForceTest failing, which as of now, we haven't had enough
time to fix. This will be addressed for the next delivery.

## Task 1 “Thermostats” ##
* We created a general ```Thermostat``` that implements some of the functionalities that thermostats have in common, such as calculating kinetic energy or calculating current temperature.
* We decided not to store a reference to the particles of the ```LinkedCellContainer``` in the thermostat. On one hand doing this would spare us some copying of the particles back and forth in each iteration. However, it would require us to keep track of when ```LinkedCellContainer``` and ```Thermostat``` are deleted and used, such as it does not come to any memory problems. We decided to try to make our code less error-prone and increase maintainability by using copies instead of references. In each iteration, we update the state of the thermostat by calling the function ```updateState``` in ```Thermostat```. This is costly as we need to copy all particles twice per iteration (once with ```getParticleVector``` and then with ```updateState```). We might change this later when we optimize. 
* We implemented three types of Thermostats. The simple and gradual thermostat, as described in the worksheet. We also have another subclass, ```FakeThermostat```. This class does not implement any functionality. It simply overrides the functions of ```Thermostat``` with functions, that do not do anything. We decided that this will make our code in the ```Simulation``` class simpler and easier to read, compared to having many if conditions that check whether a thermostat is present or not.

## Task 2 “Simulation of the Rayleigh-Taylor instability” ##
### Periodic Boundaries: ###
* The periodic boundary condition was implemented on top of the existing scheme for handling boundary conditions - meaning it also iterates over particles
* Enforce this boundary for a particle consists of two steps:
  1. Setting its internal markedForMirroring to true, so that later methods in LinkedCellContainer can mirror it
  2. Adding mirrored particles according to the geometry of periodic boundaries

The first step is trivial and the "leg work" was mostly done in ensuring that the particle to be mirrored gets deleted and a mirrored copy gets added instead

The second step is more involved and consists of the following steps:
  1. Calculating the shifted position of the particle
  2. Checking whether the shifted position overlaps with the halo region

And in order to respect the condition that not all boundaries are periodic, the shifted position is only calculated for the boundaries that are periodic.
  
### Gravity Force: ### 
* The gravity Force is a single particle force so it was not possible to implement it as a subclass of ForceCalculation.h like Lennard Jones. So we added a new parent class ```OneParticleForceCalculation``` and implemented ```GravityForce``` as a subclass of it, the method offered by this class will then be used in the Simulation class wrapped with the applyToAll functionality in every iteration.
* We support also this new routine through the XML input. The gravity factor is intialized with 0 so that this force has no effect if the user does not specify it. The user can overwrite this value with the XML input. The syntax is the following ``` <gravity> gravity factor value </gravity> ```

### Mixing rules: ### 
* We created a new class ```MixingRuleLennardJones``` that is used when multiple types of liquids interact with each other. We extended ```SphereGenerator``` and ```CuboidGenerator``` with the ability to optionally set the sigma and epsilon parameters of the liquids. Those parameters also have default values (1.0 for both) in order for the classes to be compatible with the rest of the project.

### Small Rayleigh-Taylor instability experiment: ###



https://github.com/klaramozna/PSEMolDyn_GroupD/assets/48733720/d93944b5-6c4e-4cca-b199-08d86c704d48

### Rayleigh-Taylor instability big experiment: ###



https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/05d0f0e9-53e7-4ea3-87b1-ec46292050f8




## Task 3 “Simulation of a falling drop - Liquid” ##
### Checkpointing ###

* To store checkpoints, we used the serialization functionality provided by XSD CodeSynthesis (```xsd cxx-tree --std c++11 --generate-doxygen --hxx-suffix .h --cxx-suffix .cpp  --generate-serialization ../../input/checkpointFormat.xsd ```), which generates C++ classes from an XML Schema Definition (XSD). Our approach involves defining a structured XSD format specifically for checkpoint data representation (```input/checkpointFormat.xsd```). This schema outlines the structure, elements, and data types expected within a checkpoint file (which is a sequence of particles to save the complete state of the molecules to the file, including old force, type, and so on). 
* We then utilize the generated C++ classes to serialize checkpoint data into XML format, adhering to the defined schema. This serialization ensures that the produced XML files comply with the specified format, enabling easy storage, exchange, and readability of checkpoint information.
* We added command line options to give the user the possibility to use this feature. These are explained in the repository README.
* Example Usage: Liquid Equilibration: run the program so to store the checkpoint after the liquid equilibrates in an xml file to load in next simulation   
  ```./src/MolSim -p ../input/WS4/T3-gravity-equi.xml -c ../input/Checkpoints/Checkpoint1.xml```  


https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/be2fdf83-d90f-40dc-b699-5ebfce15e9ff


* Sphere Drop accelerated by the gravity on the equilibrated liquid: run the program so to load the checkpoint and enter the sphere:  
  ```./src/MolSim -p ../input/WS4/T3-sphere.xml -x ../input/Checkpoints/Checkpoint1.xml```  
  This how it looks like when we load the checkpoint and add the sphere:  
  <img src =checkpoint_loaded.png>

### Simulation of a falling drop - Liquid ### 
* Unfortunately, we were not able to successfully perform this simulation.
* The drop falls as expected, but once it makes contact with the liquid below, the particles explode and a large amount of them leave the simulation completely.
* We have not been able to figure out the cause of this until now, however we will fix and debug this for the next worksheet.

## Task 4 “Performance Measurement and Profiling” ##

* With the profiling tool perf we used the following command to retrieve various performance metrics collected during the program's execution.
``` perf stat -o summary.txt -e cpu-cycles,cache-misses,cache-references ./src/MolSim p ../input/fallingdrop_Wall.xml -t True ```  

Results:  
```# started on Tue Dec 19 18:05:19 2023


 Performance counter stats for './src/MolSim -p ../input/fallingdrop_Wall.xml -t True':

   288.977.433.085      cpu_core/cpu-cycles/                                                    (99,96%)
   236.150.253.622      cpu_atom/cpu-cycles/                                                    (0,04%)
         3.280.184      cpu_core/cache-misses/                                                  (99,96%)
        29.063.767      cpu_atom/cache-misses/                                                  (0,04%)
        11.522.469      cpu_core/cache-references/                                              (99,96%)
       184.805.235      cpu_atom/cache-references/                                              (0,04%)

      71,814849566 seconds time elapsed

      71,682916000 seconds user
       0,027987000 seconds sys
```  
Interpretation:  
* It is clear that the program utilizes heavily the CPU as we are performing many calculations during many iterations.
* Ratio of Cache Misses to Cache References: Cache references represent the total number of times the CPU accesses the cache memory, while cache misses occur when the CPU cannot find the needed data or instructions in the cache, resulting in a need to fetch the information from a slower memory level like RAM, impacting the program's speed due to increased latency.
From the stats we can derive an average ```ratio of cache misses to cache references``` between the CPU core and CPU atom of approximately ```22%```. This ratio isn't extremely high but still it is a potential room for optimization to reduce cache miss rates and further enhance performance.  
  
Which parts of the code consume the most runtime?  

* We used the ```perf``` profiler with the falling drop simulation to find out where our code needs more optimizations. The results were the following: (the picture bellow only includes functions with time percentages above 1%)
<img src="profiling_result.png">
* The most time by far was consumed by different array operations. This was expected, as most of the attributes that are simulated (velocity, position, force) are stored in arrays. Those attributes are accessed and changed many times for each particle in every iteration.
* Next comes the ```VectorDouble``` constructor. We use ```VectorDouble``` to perform operations on vectors, such as addition, scaling, calculating distances or norms etc. Each time we want to do an operation on a particle attribute. We need to create a ```VectorDouble``` that corresponds to the attribute of the particle, as the particles are stored as arrays and not as ```VectorDouble```. These operations, again, are performed many times for each particle in each iteration.
* Another function that needs a lot of time is ```applyToPairs```. This is not too surprising as we need to iterate through many combinations of pairs of particles each iteration to calculate the forces. It might also be caused be the many index calculations (for example with the function getGridIndex() that also take up a lot of time).
* The ```getL2Norm``` function is a candidate for optimization as well. The high time spent in this function is probably due to the square root computation and generally being used many times in an iteration.

### CoolMUC2  ###
* we succefully performed the log in process to the linux cluster with the provided login credentials + 2FA.
* At first we had problems compiling our program on the cluster because of the xerces library, we had to make some changes in our CMake files (we now use PkgConfig to check for xerces) to overcome that.
* Those are the steps we perform on the linux cluster to compiler our code:   
  1 - Copy project from local device to the cluser: ```$ scp -r ./PSEMolDyn_GroupD di29wav@lxlogin1.lrz.de:~/```   
  2 - Load the needed modules on the cluster (gcc, cmake, boost, pkgconf, xerces-c): ```$ module load <module_name>```   
  3- create a build folder, switch to it and compile without tests: ```$ cmake -DBUILD_GTESTS=OFF ..``` then ```$ make```   
* To run for example the fluid equilibration we used the following script:  
```
#!/bin/bash
#SBATCH -o ./%x.%j.%N.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=serial
#SBATCH --partition=serial_std
#SBATCH --mail-type=end
#SBATCH --mail-user=rayen.manai@tum.de
#SBATCH --export=ALL
#SBATCH --time=01:15:00

srun ./src/MolSim -p ../input/WS4/T3-gravity-equi.xml -t True
``` 
## Task 5 “Tuning the sequential Performance” ##
### Thermostat optimization ### 
* First, we tried to optimize our thermostat. As we explained in the beginning, thermostat does not store a reference to the particles, and needs to be updated in each iteration with ```updateState```. This requires the particles to first be copied in the ```getParticleVector``` function and then again in ```updateState``` - so all particles are copied twice per iteration. This presents a significant performance overhead, especially as the number of particles rises.
* However, doing this copying operation is not necessary in every iteration, as the thermostat is not applied every time. The thermostat is typically only applied once every few hundreds of iterations, so the update is also only necessary in those iterations where the thermostat is actually applied.
* For this optimization, we adjusted the ```updateState``` function to only be applied in the relevant iterations and created a new function ```updateStateTest``` that maintains the old functionality and compared those two using the falling drop simulation.
* We first compared the measurements using the -O3 flag, applying the thermostat every 1000 iterations. The measurements for both functions were comparable, both very close to 100 seconds. To make sure that this was not caused by not applying the thermostat too infrequently, we tried again, applying the thermostat every 100 iterations, but with the same result - both functions had more or less the same runtime, once again around 100 seconds.
* We thought that possibly -O3 already did this optimization for us which is why our optimization does not make a difference. However, we got the same results using -O0, with both versions taking around 1000 seconds.
* We suspect the reason why this optimization did not speed up our simulation is that a lot more time is spent on calculating forces, creating VectorDoubles etc, compared to the ```updateState``` function, as we saw in the profiling results. So this optimization is not significant in the grand scheme of things.
* Because this optimization did not change anything, we didn't merge it into ```main```. If you want to look at it, it is in the last commit (6a4f19a) on the branch ```thermostat-optimization```.

### Particle optimization ### 
* This optimization is based on the profiling results. The repeated construction of ```VectorDouble``` objects takes up around 5% of the time of the entire simulation. One reason we call the ```VectorDouble``` constructor so often is because the three-dimensional attributes in the ```Particle``` class (velocity, position...), are stored as an array. The ```Particle``` class offers a getters that return arrays, but most of the time, we do not just need the values, we need to perform calculations on attributes. For this reason, we most often use the ```get<attribute_name>Vector()``` getters that return a ```VectorDouble```. The same applies for the setters that take a ```VectorDouble``` as a parameter as well. 
* This leads to very frequently needing to construct a ```VectorDouble``` from an array and vice versa. To reduce the amount of ```VectorDouble``` and ```std::array``` constructor calls, we decided to store the attributes in ```Particle``` as ```VectorDouble``` instead of an array.
* This optimization yielded results. We measured the performance once again with the falling drop simulation, this time not using the thermostat. Even with -O3 turned on, we measured a runtime around 10% lower after the optimization - ca 77 seconds before and ca 87 seconds after. (We say around, not exact numbers, because we measured each simulation at least two times and took an average, so that we can confirm that the difference is not a result of for example different OS scheduling during the simulation.)

### Lookup table for getGridIndex ### 
* Next, we optimized the ```getGridIndex``` function in ```LinkedCellContainer```, as it was one of the functions relatively high up on the profiler in terms of percentage of time spent in this function during the simulation.
* Instead of calculating the values on the spot every time this function is called, we precalculated all valid values for x, y, z with their corresponding indices in the grid and created a lookup table.
* Unfortunately, this optimization did not speed up the simulation. We measured both the before and after with the -O3 optimization and both values fluctuated around 85 seconds (again, fluctuated because we performed each simulation multiple times). 
* The reason this probably did not affect the execution time that much, is that although ```getGridIndex``` was one of the top functions in the profiler, it still only took about 2.7% of the total simulation. The ```getGridIndex``` calculation was already very simple and fast before the optimization, so the speedup from using a lookup table probably isn't that large. Even if we halved the time spent in this function, we would only reduce the original execution time by 1.35% so less than 1.2 seconds. The variability of the execution times within the same simulation was already around 1 second, so such a small difference would be very difficult to measure.
* Because this optimization did not bring results, we didn't merge it into ```main```. If you want to look at it, it is in the last commit (ce1ac04) on the branch ```getgridindex-optimization```.

### SIMD for VectorDouble ### 
* Another optimization we attempted was using SIMD instructions in the +, * and - operators of ```VectorDouble```. We selected those three operators because they are the most commonly used ones. They are used thousands of times in each iteration in force, position, velocity calculation and more.
* In each vector operation, for example addition, we need to do three calculations as the vectors are of size 3. Using SIMD instructions with registers that are 256 bits long (4 doubles fit in them), we could reduce the three operations to just one.
* Unfortunately, this did not lead to the desired results. With -O3 on, the time before the change was 186 seconds and 187 seconds after. We thought this might be because the overhead of using SIMD (for example loading data to and from the SIMD registers) is greater than the benefit of executing multiple instructions at once. Another explanation would be the use of the -O3 flag. With this optimization level, vectorization is enabled and it is possible that it was already performed by the compiler automatically.
* To exclude this, we performed another simulation (a shorter one this time) using the -O0 flag. This brought even worse results, with the unoptimized version taking 453 seconds and the optimized one 508 seconds.
* Because this optimization was not successful, we didn't merge it into ```main```. If you want to look at it, it is in the last commit (07be9d3) on the branch ```Simd-optimization```.

### Mixing Rules Optimization ###
* Lorentz-Berthelot mixing rule for calculating lennard Jones parameters of two molecules of different types has also a potential of improvement when calculating epsilon.  
* The first implementation of $` \epsilon_{ij} = \sqrt{\epsilon_i \cdot \epsilon_j} `$ was to just directly calculate it whenever calculateForce get called for each pair (```double eps = sqrt(p1.getEpsilon() * p2.getEpsilon());```)  
* As $` \epsilon_{ij} = \sqrt{\epsilon_i \cdot \epsilon_j} = \sqrt{\epsilon_i} \cdot sqrt{\epsilon_j} `$ and if $` \epsilon_i == \epsilon_j `$ then $` \epsilon_{ij} = \epsilon_i `$ we wanted to take advantage of those propreties.
* To incorporate those two improvements we added an attribute ```sqrtEps``` which will be computed only once the particle is created and then reused in this calculation and we added an if statement to check for the second proprety. The implementation of these optimizations can be found on the last commit on the branch ```mixingRulesOptimizations``` and will be first merged when we fix some issues with our code in main.
* Results: in our testing case (liquid equilibration) this did not show a relevant difference, the running times before and after the optimizations are roughly the same but we still find those propreties very helpful as they spare some computations in the program logic.
### cmath Sqrt vs Newton's Method ###
* In our code we use the ```sqrt``` function from the the C++ Standard Library <cmath> for example in the class ```VectorDouble3``` to calculate the L2Norm. We wanted to try to change it with the ```Newton's method``` to find the square root, but this showed worser results (arround 28% slower when testing with the falling drop simulation of WS3).  This is the case because the C++ Standard Library's mathematical functions, including sqrt(), are often implemented in a way that takes advantage of hardware-specific instructions and optimizations provided by the underlying system or compiler. Therefore this optimization was not merged in main. Its implementation can be found on the last commit on the branch ```newtonSqrt``` 
# Misc #

### Pending WS3 ### 
* Falling Drop Simulation:
  


https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/270aacd1-1df2-4ef6-997c-75fba459e1a4




https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/8e781b10-7655-4623-b6b6-fd95094c5686

### CL arguments vs XML parameters Periority ###
* We omitted the default parameters from WS1 that came with the command line arguments because they are no longer compatible and relevant for the simulations we do now, the default values should be provided through the xml files that we provide. That means now when the user starts the program with an xml file that we provide or a file the user writes compatible to our syntax ```/input/simulationFormat.xsd``` then the default values will be read from there. But we gave then periority to the command line arguments to allow the user to overwrite certain parameters in a fast way. Parameters (like end_time, delta_t, log level or force used ...) that were passed through command line arguments have periority over the ones from the provided xml file.

