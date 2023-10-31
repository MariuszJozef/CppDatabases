#[==================================================[
Import pre-build SHARED LIBRARY which is already installed somewhere 
but it is without *config.cmake, therefore absolute paths to 
*.h, *.lib, *.dll, *.so must be specified
#]==================================================]
if (WIN32 OR MSVC)
    
    set(importSharedLibName libmysql)
    set(absolutePathToSharedLibInstallTrunk "C:/Program Files/MySQL/MySQL Server 8.0")
    set(CMAKE_FIND_LIBRARY_SUFFIXES "dll")
    set(absolutePathToFile_dll_so_dylib 
        ${absolutePathToSharedLibInstallTrunk}/${CMAKE_INSTALL_LIBDIR}
    )
    
    set(absolutePathToFile_lib 
        ${absolutePathToFile_dll_so_dylib}
    )
    
    set(absolutePathToFile_h 
        ${absolutePathToSharedLibInstallTrunk}/${CMAKE_INSTALL_INCLUDEDIR}
    )

elseif(LINUX)

    # set(importSharedLibName libmysqlclient_r)
    set(importSharedLibName libmysqlclient)
    set(absolutePathToSharedLibInstallTrunk /usr)
    set(CMAKE_FIND_LIBRARY_SUFFIXES "so")
    set(absolutePathToFile_dll_so_dylib 
        ${absolutePathToSharedLibInstallTrunk}/${CMAKE_INSTALL_LIBDIR}
    )

    set(absolutePathToFile_h 
        ${absolutePathToSharedLibInstallTrunk}/${CMAKE_INSTALL_INCLUDEDIR}/mysql
    )

elseif(APPLE)

    set(CMAKE_FIND_LIBRARY_SUFFIXES "dylib")

elseif (UNIX AND NOT APPLE)

    set(CMAKE_FIND_LIBRARY_SUFFIXES "so")

endif()

#[==================================================[
Add the library with info about its location
#]==================================================]
add_library(MySql::MySql SHARED IMPORTED)

target_include_directories(MySql::MySql
    INTERFACE
        ${absolutePathToFile_h}
)

if (WIN32 OR MSVC)

    set_target_properties(SharedLib::SharedLib
        PROPERTIES
            IMPORTED_LOCATION   ${absolutePathToFile_dll_so_dylib}/${importSharedLibName}.${CMAKE_FIND_LIBRARY_SUFFIXES} # *.dll, *.so, *.dylib
            IMPORTED_IMPLIB     ${absolutePathToFile_lib}/${importSharedLibName}.lib # only relevant for Windows
    )

else()

    set_target_properties(MySql::MySql
        PROPERTIES
            IMPORTED_LOCATION   ${absolutePathToFile_dll_so_dylib}/${importSharedLibName}.${CMAKE_FIND_LIBRARY_SUFFIXES} # *.dll, *.so, *.dylib
    )

endif()
