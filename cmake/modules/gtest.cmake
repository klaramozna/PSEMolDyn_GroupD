# make gtest optional 
option(BUILD_GTESTS "Build Google Tests" ON)

if(BUILD_GTESTS)
        include(FetchContent)
        message("Building GTests")
        # Fetch GoogleTest
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
            DOWNLOAD_EXTRACT_TIMESTAMP true
        )

        FetchContent_MakeAvailable(googletest)
        # Look for GoogleTest
        find_package(GoogleTest QUIET)

else()
    message("Skipping GTests")
endif()