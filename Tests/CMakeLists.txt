#[==================================================[
Find or fetch a library and display its cmake targets
#]==================================================]
option(linkGTestAsSharedLibrary "OFF to link as static library, ON as dynamic - on Windows the latter requires the *.dll to be copied next to the .exe (this is done in add_subdirectory)" OFF)

if(linkGTestAsSharedLibrary)
    set(isThereDllToLinkToUnitTestDatabase ON)
    message(STATUS "linkGTestAsSharedLibrary: " ${linkGTestAsSharedLibrary} " --- googletest will be linked as SHARED library")
else()
    set(isThereDllToLinkToUnitTestDatabase OFF)
    message(STATUS "linkGTestAsSharedLibrary: " ${linkGTestAsSharedLibrary} " --- googletest will be linked as STATIC library")
endif()

include(${CMAKE_SOURCE_DIR}/CMakeUtils/FindOrFetch/FindOrFetchGTestGMock.cmake)

get_property(importTargets1 DIRECTORY ${SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
message(STATUS "importTargets1: ${importTargets1}")

#[==================================================[
Build (sub)project(s) tests
#]==================================================]
add_subdirectory(Unit/Databases)

#[==================================================[
Run tests
#]==================================================]
add_custom_target(runUnitTest
    COMMAND ${CMAKE_COMMAND} -E echo "execute: $<TARGET_FILE:targetUnitTestDatabase>"
    COMMAND $<TARGET_FILE:targetUnitTestDatabase>
)

add_custom_target(runAllTests
    COMMAND ${CMAKE_COMMAND} -E echo "execute: $<TARGET_FILE:targetUnitTestDatabase>"
    COMMAND $<TARGET_FILE:targetUnitTestDatabase>
)
