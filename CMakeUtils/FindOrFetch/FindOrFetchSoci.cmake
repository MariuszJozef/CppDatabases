#[==================================================[
Find or fetch prerequiste libraries for SOCi  and display their cmake targets
#]==================================================]
include(GNUInstallDirs)

include(${CMAKE_CURRENT_LIST_DIR}/FindDoNotFetchBoost.cmake)

get_property(importTargets1 DIRECTORY ${SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
message(STATUS "importTargets1: ${importTargets1}")

include(${CMAKE_CURRENT_LIST_DIR}/FindDoNotFetchMySql.cmake)

get_property(importTargets2 DIRECTORY ${SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
list(REMOVE_ITEM importTargets2 ${importTargets1})
message(STATUS "importTargets2: ${importTargets2}")

#[==================================================[
Find preinstaled soci package (either static or shared) 
or if it cannot be found, fetch it from github and build it with the project
#]==================================================]
set(packageName SOCI)
set(packageVersion 4.0.3)

#[==================================================[
Point the path to ${packageName}Config.cmake or ${packageName}-config.cmake
if the package is not on the standard search path nor in CMAKE_INSTALL_PREFIX
#]==================================================]
if(linkSociAsSharedLibrary)

    message(STATUS "linkSociAsSharedLibrary: " ${linkSociAsSharedLibrary} " --- SOCI will be linked as SHARED library")

    if (WIN32 OR MSVC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".dll")
        set(${packageName}_DIR C:/Packages/Soci4.0.3/shared/lib/cmake/SOCI)
    elseif(LINUX)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
        set(${packageName}_DIR /opt/soci4.0.3/lib64/cmake/SOCI)
    elseif(APPLE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".dylib;.so")
        set(${packageName}_DIR )
    elseif (UNIX AND NOT APPLE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
        set(${packageName}_DIR )
    endif()

else()

    message(STATUS "linkSociAsSharedLibrary: " ${linkSociAsSharedLibrary} " --- SOCI will be linked as STATIC library")

    if (WIN32 OR MSVC)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
        set(${packageName}_DIR C:/Packages/Soci4.0.3/static/lib/cmake/SOCI)
    elseif(LINUX)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(${packageName}_DIR /opt/soci4.0.3/lib64/cmake/SOCI)
    elseif(APPLE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(${packageName}_DIR )
    elseif (UNIX AND NOT APPLE)
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        set(${packageName}_DIR )
    endif()

endif()

# Omit REQUIRED keyword so as to be able to fetch the package if it is not installed
find_package(${packageName} ${packageVersion})

if(${packageName}_FOUND)
    message(STATUS "${packageName}_FOUND: ${${packageName}_FOUND}")
    message(STATUS "${packageName}_VERSION: ${${packageName}_VERSION}")
    message(STATUS "${packageName}_INCLUDE_DIRS: ${${packageName}_INCLUDE_DIRS}")
    message(STATUS "${packageName}_LIBRARIES: ${${packageName}_LIBRARIES}")
    message(STATUS "${packageName}_DIR: ${${packageName}_DIR}")
    message(STATUS "CMAKE_FIND_LIBRARY_SUFFIXES: ${CMAKE_FIND_LIBRARY_SUFFIXES}")
else()
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)

    if(linkSociAsSharedLibrary)
        set(SOCI_SHARED ON)
        set(SOCI_STATIC OFF)
    else()
        set(SOCI_SHARED OFF)
        set(SOCI_STATIC ON)
    endif()

    set(WITH_ORACLE OFF)
    set(WITH_FIREBIRD OFF)
    set(WITH_DB2 OFF)
    set(SOCI_TESTS OFF)
    
    set(WITH_BOOST ON)
    set(BOOST_INCLUDE_DIR /usr/include/boost)
    set(CMAKE_INSTALL_PREFIX /opt/soci4.0.3)

    set(WITH_SQLITE3 ON)
    set(SQLITE3_INCLUDE_DIR /usr/include)
    set(SQLITE3_LIBRARY /usr/lib64/libsqlite3.so)

    set(WITH_MYSQL ON)
    set(MYSQL_INCLUDE_DIR /usr/include/mysql)
    set(MYSQL_LIBRARIES /usr/lib64/libmysqlclient.so)

    set(WITH_POSTGRESQL ON)
    set(POSTGRESQL_INCLUDE_DIR /usr/include)
    set(POSTGRESQL_LIBRARY /usr/lib64/libpq.so)

    set(WITH_ODBC ON)
    set(ODBC_INCLUDE_DIR /usr/include)
    set(ODBC_LIBRARIES /usr/lib64/libodbc.so)
    
    FetchContent_Declare(soci
        GIT_REPOSITORY  https://github.com/SOCI/soci.git
        GIT_TAG         v4.0.3
        SOURCE_DIR      ${CMAKE_SOURCE_DIR}/External/Soci4.0.3
        GIT_PROGRESS    TRUE
        GIT_SHALLOW     TRUE
        USES_TERMINAL_DOWNLOAD TRUE   # <---- only used by Ninja generator
    )

    FetchContent_MakeAvailable(soci)
endif()
