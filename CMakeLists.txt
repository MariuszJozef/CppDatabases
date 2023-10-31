cmake_minimum_required(VERSION 3.26.0...3.26.3)

include(CMakeUtils/Handy/DisallowInSourceBuilds.cmake) # Comment out to allow
include(CMakeUtils/Handy/SelectCompilerViaFlagIfNotUsingCMakePresets.cmake) # or else default compiler will be used

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
project(CppDatabase VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

include(CMakeUtils/Handy/DisplayGenericInfo.cmake) # Comment out to suppress

#[==================================================[
Build tests and mocks
#]==================================================]
include(CTest) # Comment out this line to switch off tests and mocks (but only to fix compilation/link errors!)
if(BUILD_TESTING)
    add_subdirectory(Tests)
endif()

#[==================================================[
Build (sub)project(s)
#]==================================================]
add_subdirectory(Code/Databases)

#[==================================================[
Run all tests and program excutables; in case tests were switched off, 
there is a target "run" just for the program executable
#]==================================================]
if(BUILD_TESTING)
    add_custom_target(runAll
        COMMAND ${CMAKE_COMMAND} -E echo "execute: $<TARGET_FILE:targetUnitTestDatabase>"
        COMMAND $<TARGET_FILE:targetUnitTestDatabase>

        COMMAND ${CMAKE_COMMAND} -E echo "execute: $<TARGET_FILE:targetDatabase>"
        COMMAND $<TARGET_FILE:targetDatabase>
    )
endif()

#[==================================================[
(Optional) IDE solution name
Must be after all other projects since last project(...) is used as solution name
#]==================================================]
if (CMAKE_GENERATOR MATCHES "Visual Studio" OR  # any VS generator
    CMAKE_GENERATOR MATCHES "Eclipse CDT4")     # any Eclipse generator

    project(CppDatabaseWithTests)

endif()
