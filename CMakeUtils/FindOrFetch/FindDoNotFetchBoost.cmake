#[==================================================[
Find preinstaled Boost package
Do NOT fetch because building takes too long!
#]==================================================]
set(packageName Boost)
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_USE_MULTITHREADED ON)

#[==================================================[
Point the path to ${packageName}Config.cmake or ${packageName}-config.cmake
if the package is not on the standard search path nor in CMAKE_INSTALL_PREFIX
#]==================================================]
if (WIN32)
    set(${packageName}_DIR C:/Packages/Boost1.82.0/static/lib/cmake/Boost-1.82.0)
    set(packageVersion 1.82.0)
elseif(LINUX)
    set(${packageName}_DIR /usr/lib64/cmake/Boost-1.78.0)
    set(packageVersion 1.78.0)
elseif(APPLE)
    set(${packageName}_DIR /usr/local/Cellar/boost/1.71.0/lib/cmake/Boost-1.71.0)
    set(packageVersion 1.71.0)
elseif(UNIX AND NOT APPLE)
    set(${packageName}_DIR )
endif()

find_package(${packageName} ${packageVersion} COMPONENTS date_time REQUIRED)

if(${packageName}_FOUND)
    message(STATUS "${packageName}_FOUND: ${${packageName}_FOUND}")
    message(STATUS "${packageName}_VERSION: ${${packageName}_VERSION}")
    message(STATUS "${packageName}_INCLUDE_DIRS: ${${packageName}_INCLUDE_DIRS}")
    message(STATUS "${packageName}_LIBRARIES: ${${packageName}_LIBRARIES}")

    include_directories("${Boost_INCLUDE_DIRS}")
endif()
