# Collect all cpp files in the 'src' directory
file(GLOB_RECURSE MY_SRC
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

# Create a library target for the project code
add_executable(MolSim ${MY_SRC})

# Include directories specific to the 'src' directory, if needed
target_include_directories(MolSim
        PUBLIC ${CMAKE_SOURCE_DIR}/libs/libxsd
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

# Configure dependencies - Boost, Xerces
find_package(XercesC REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

# Link Libraries for running the project
target_link_libraries(MolSim
        # stuff that is used in headers and source files
        PUBLIC
        xerces-c
        Boost::program_options
)

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
