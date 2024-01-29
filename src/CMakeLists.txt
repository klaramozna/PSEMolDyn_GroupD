# Collect all cpp files in the 'src' directory
file(GLOB_RECURSE MY_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Create a library target for the project code
add_executable(MolSim ${MY_SRC}
Simulation/Physics/GravitationalForce.cpp
        Particles/ParticleGenerator.cpp
        Particles/ParticleGenerator.h
        utils/CuboidGenerator.cpp
        utils/CuboidGenerator.h
        utils/MembraneGenerator.cpp
        utils/MembraneGenerator.h
        utils/SphereGenerator.cpp
        utils/SphereGenerator.h
        Particles/ParticleContainer.h
        Particles/LinkedCellContainer.cpp
        Particles/LinkedCellContainer.h
        Particles/Cell.cpp
        Particles/Cell.h
        Particles/Boundary.cpp
        Particles/Boundary.h
        utils/CuboidGenerator.h
        IO/xsdCode/commonSchema.cpp
        IO/xsdCode/checkpointFormat.cpp
        IO/xsdCode/simulationFormat.cpp
        IO/input/XMLReader.cpp
        IO/input/CuboidReader.cpp
        IO/input/FileReader.cpp
        IO/input/CheckpointReader.cpp
        Benchmark.cpp
        Simulation/Thermostat.cpp
        Simulation/Thermostat.h
        Simulation/SimpleThermostat.cpp
        Simulation/SimpleThermostat.h
        Simulation/GradualThermostat.cpp
        Simulation/GradualThermostat.h
        Particles/BoundaryEnforcer.cpp
        Particles/BoundaryEnforcer.h
        utils/BoundaryTypes.h
        utils/Constants.h
        utils/BoundaryDirection.h
        Simulation/Physics/MixingRuleLennardJones.cpp
        Simulation/Physics/MixingRuleLennardJones.h
        Simulation/Physics/GravityForce.cpp
        Simulation/Physics/HardcodedPullForce.cpp
        Simulation/Physics/TruncatedLennardJones.cpp
        Simulation/FakeThermostat.cpp
        Simulation/FakeThermostat.h
        utils/MaxwellBoltzmannDistribution.h
        Simulation/TempDifferenceThermostat.cpp
        Simulation/TempDifferenceThermostat.h
        Particles/ParticleStatistics.cpp
        Particles/ParticleStatistics.h
)
        
## Include directories specific to the 'src' directory, if needed
target_include_directories(MolSim
PUBLIC ${CMAKE_SOURCE_DIR}/libs/libxsd
PUBLIC ${CMAKE_SOURCE_DIR}/libs/
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
#uncomment this on the cluster
#PUBLIC /dss/dsshome1/lxc04/di29wav/
)
find_package(PkgConfig REQUIRED)
pkg_check_modules(XERCESC REQUIRED IMPORTED_TARGET xerces-c)

target_link_libraries(MolSim
# stuff that is used in headers and source files
        PUBLIC
                PkgConfig::XERCESC
                Boost::program_options
)


# Configure dependencies
find_package(Boost REQUIRED COMPONENTS program_options)

# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>:-Wall>
        # disable some spam warnings for icpc...
        $<$<CXX_COMPILER_ID:Intel>:-w3 -wd383,981,1418,1572,2259>
)

# set cxx standard. You may raise this if you want.
target_compile_features(MolSim
        PRIVATE
        cxx_std_17
)




