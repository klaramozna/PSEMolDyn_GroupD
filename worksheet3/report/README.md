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
## Task 1 ”XML input” ##

* We downloaded the tool Codesynthesis XSD from its webpage (https://www.codesynthesis.com/products/xsd/download.xhtml). We chose to install the version ```4.0.0``` so that it is compatible with the libxsd that is already povided in our project under libs.
* We made ourselves familiar with the tool by reading some documentation on the getting started and playing arround with some examples.
* We defined ```simulationFormat.xsd``` which serves as a specification that defines the structure, constraints, and data types of XML documents. Its role is primarily to describe the valid elements, attributes, their relationships, and content for an XML document which in our case will be provided by the user as a convenient way to specify all the simulation parameters and particles.
* We used the Codesynthesis XSD tool to generate C++ classes based on the structure defined in that specified XSD (XML Schema Definition) file by running the command ```xsd cxx-tree --std c++11 --generate-doxygen --hxx-suffix .h --cxx-suffix .cpp  ../../../input/simulationFormat.xsd```
* We used the following options: ```--std ``` to specify the C++ standard to be used, ```--generate-doxygen``` to enable the generation of Doxygen.style documentation which fits well with our project because that's what we are using, and finally ```--hxx-suffix``` and ```--cxx-suffix``` to change the used suffixes for the generated C++ header and source file to be consistent with the whole project.   
* We provided in ```/input``` an example of such input file (```twoBodiesCollision.xml```) which runs the simulation Collision of two bodies from worksheet 2. The user just needs to run the program with that input file and everything related to the simulation will be read from that file.       
``` ./src/MolSim -p ../input/twoBodiesCollision.xml ```
* For now our program supports both possibilities for input files: either a user enters an .xml file which follows our format and all the simulation parameters will be read from it, or one could use the .txt specified file formats and pass the needed arguments via command line options. Our program does the distinction based on the file extension.


## Task 2 ”Linked-cell algorithm” ##
* Since we now have a second implementation of the ```ParticleContainer``` from previous week. We decided rename ```ParticleContainer``` to ```DirectSumContainer``` and create a superclass ```ParticleContaier``` that both ```DirectSumContainer``` and the new ```LinkedCellContainer``` inherit from. 
* ```ParticleContainer``` contains virtual methods that allow us to choose the container used at runtime.
* We store particles in a vector of ```Cells```. The ```Cell``` class is implemented as a list of particles. We decided to use a list and not a vector, because we need to move particles between cells as they move. In order to do this, we need to delete the particle in the original cell and add it to the new cell. Adding a particle to a vector should not be too inefficient given that we reserve enough space in the beginning, but deleting a particle would be very inefficient in a vector, especially if the particle is located in the middle of the vector, as all of the elements after that would need to be moved. For that reason with decided to implement ```Cell``` as a list.
* The most interesting part of the ```LinkedCellContainer``` class is the ```applyToPairs``` method we use for force calculation. To iterate over the cells, we use the position of a cell, which is the place of the cell along each axis. For example position (0, 1, 2) would mean that the cell is the first cell along the x-axis, second cell along the y-axis and third cell along the z-axis.
* We then map this position onto an index in the vector of cells using a simple formula taken from the book "Numerical Simulation in Molecular Dynamics".
* Using the position of a cell, we find all of its neighbours and let its particles interact with the particles of the neighbours. In order to still be able to use Newton's third law, we only consider neighbours that a larger cell index than the current cell. Within a cell, we use an implementation very similar to the one from last week, just adapted to a list.

## Task 3 "Boundary conditions" ##


## Task 4 ”Simulation of a falling drop - Wall” ##
* We extended the particle generator with another subclass to generate spheres. The math behind generating particles within a sphere involves the equation for a sphere and the calculation of distances to determine if a point lies within the sphere.
* Equation of a Sphere with a center (a, b, c) and radius r is given by: $`(x−a)^2+(y−b)^2+(z−c)^2=r^2 `$ , so we loop over the coordinates and check only generate a particle on those coordinares when they lie within the sphere.
* Here is an example of a generated shpere:   
<img src=Sphere.png>  

* We also adapted the XML input format accordingly to allow the user to also specify the parameters needed to describe a sphere by defining a complexType ```Sphere```. An example of a sphere generating XML file is ```input/sphere.xml```


  
# Misc #

