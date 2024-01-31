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
## Task 1 ”Simulation of a membrane” ##
* We chose the option to extend the particle class over the choice of having a seperate class for membranes to easily intergrate the functionality with the linked cell container and avoid some refactoring work.
* We extended the particle class to support attributes like average bond length, stiffness, parallel/diagonal neighbors, a particle id and a flag to mark if the hard coded pull force will be applied to this  particle or not.
* We store the neighbours in a vector of shared pointers so that the pointers don't change when we give the particles back fron the membranegenerator to the container.
* We implemented a membrane Generator which will complete the following tasks: 
1- generate a cuboid with the parameters given in the input file, and if present mark the particles with the flag if the pull force is activated on them
2- initialize the neighbours vectors of each particle: for that we have two helper functions ``` calculateParallelNeighbourIndices ```  and ```calculateDiagonalNeighbourIndices``` that hold the logic of calculating the neighbours of each particle, and counting for the edge cases.  
The basic idea of these two methods can be seen in the following presentation:  
<img src="Membrane_idea.jpg">  

* The harmonic forces were integrated into the simulation.cpp file, where this method will be applied on all the particles each iteration.
* To avoid self-penetration, we implemented the TruncatedLennardJones forces, the xml input datei allows to specify this type of force which is just the repulsive part of the LennardJones Potential.
* We also managed to give the user the ability to specify in the input file exactly the end time of the "hardcoded" pull force, on which particles will it be applied and with which factors, an example of this syntax can be seen in the file /input/WS5/membrane.xml.  
  
<img src="membrane_initialization.png">

#### Tests #####
* To test that the neighbours are correctly intialised we wrote tests in ```MembraneGeneratorTest.cpp```, that generate a 3*3 Membrane and then check all neighbours of all 9 particles.
* In ```MembraneForcesTest.cpp``` we tested some values of one iteration of Harmonic Forces against hand calculated values, as well as for Truncated (repulsive) Lennard Jones.  

## Task 2 ”Parallelization” ##


## Task 3 "Rayleigh-Taylor instability in 3D" ##
*


## Task 4 ”Nano-scale flow simulation (Option A)” ##
* 

https://github.com/klaramozna/PSEMolDyn_GroupD/assets/101558922/9114c752-507f-451b-ae8c-396a3f36a02d



## Task 5 ”Crystallization of Argon (Option B)” ##

  
# Misc #
* We did a lot of refactor work to be able to integrate the new functionalities of this worksheet: 
  
#### Solve dependency between ParticleReader and ParticleContainer ####
* We had from previous implementations the design flaw that caused a circular dependeny between ParticleReaders (for example the XMLReader) and the ParticleContainer (for example LinkedCellContainer): the problem was that the method readFile expects a ParticleContainer as argument and then fills that container with the particles read from the file, this was problematic because the linked cell container can first be instantiated after reading the needed parameters for it from readFile (like size, boundaries, cutoff radius ...), we avoided that before with some workarounds but now we fixed the design by breaking this dependency: ParticleReaders now have an intern vector of shared pointers to the Particles, when readFile is called the vector is filled with the read particles (+ of course simulation parameters are stored in SimParameters) and then when we instantiate the LinkedCellContainer for example we call getParticles from the reader to get the vector of particles and add them to the container. 


#### Simulation Iterations to the right place #####
* Before we had the simulation iterations logic in the main file (MolSim.cpp), this was clearly a bad design and also made it hard to integrate the membrane implementation (the pull force), because in the Simulation class we would we need to keep track of the current time to know if this pull force is still active or not (as it has a different end time then the whole simulation).
* We made the needed refactor to move all the simulation Logic to the Simulation Class.