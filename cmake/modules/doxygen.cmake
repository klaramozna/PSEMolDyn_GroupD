# make doc_doxygen optional if someone does not have / like doxygen

# TODO: create CMake build option for the target.
option(BUILD_DOXYGEN "Build Doxygen documentation" OFF)

# TODO: Add a custom target for building the documentation.
if(BUILD_DOXYGEN)

    find_package(Doxygen QUIET)
    if(NOT Doxygen_FOUND)
        message(FATAL_ERROR "Doxygen not found. You can install it with: sudo apt-get install doxygen")
    endif()

    add_custom_target(doc_doxygen
    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/../Doxyfile
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/../
    COMMENT "Generating Doxygen documentation"
    )
    # Exclude Doxygen target from default target (all)
    set_target_properties(doc_doxygen PROPERTIES EXCLUDE_FROM_ALL TRUE)
else()
    message("Skipping documentation")
endif()
