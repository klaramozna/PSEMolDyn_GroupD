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

## Task 3 "Boundary conditions" ##


## Task 4 ”Simulation of a falling drop - Wall” ##

  
# Misc #

