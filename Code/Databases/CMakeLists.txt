#[==================================================[
Database (executable program)
#]==================================================]
add_executable(targetDatabase) 

target_include_directories(targetDatabase
    PRIVATE
        hdr
        ./include
)

target_sources(targetDatabase
    PRIVATE
        src/MainDatabase.cpp
        ./include/Common.hpp
        ./include/DatabaseApi.hpp
        src/DatabaseApi.cpp
        hdr/Database.hpp
        src/Database.cpp
        hdr/DatabaseSqlite.hpp
        src/DatabaseSqlite.cpp
        hdr/DatabaseMySql.hpp
        src/DatabaseMySql.cpp
        hdr/DatabasePostgreSql.hpp
        src/DatabasePostgreSql.cpp
        hdr/DatabaseMsSqlServer.hpp
        src/DatabaseMsSqlServer.cpp
        hdr/TableRecords.hpp
        src/TableRecords.cpp
        hdr/ConvertRecordTypes.hpp
)

set_target_properties(targetDatabase
    PROPERTIES
        OUTPUT_NAME                         Database_${sharedOrStaticType}
        EXPORT_NAME                         Database
        DEBUG_POSTFIX                       "_d"
        RUNTIME_OUTPUT_DIRECTORY            ${CMAKE_BINARY_DIR}/buildOut/Databases/bin/$<CONFIG>
        PDB_OUTPUT_DIRECTORY                ${CMAKE_BINARY_DIR}/buildOut/Databases/pdb/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY_<Config>   ${RUNTIME_OUTPUT_DIRECTORY}
        PDB_OUTPUT_DIRECTORY_<Config>       ${PDB_OUTPUT_DIRECTORY}
)

target_compile_features(targetDatabase
    PUBLIC
        cxx_std_20
)

if(MSVC)

    target_compile_options(targetDatabase 
        PRIVATE
            /EHsc
            /W2
            # /Wall
    )

else()

    target_compile_options(targetDatabase 
        PRIVATE
            -Wall
            # -Wextra
            # -Wpedantic
    )

endif()

#[==================================================[
Find or fetch SOCI library and display its cmake targets
#]==================================================]
option(linkSociAsSharedLibrary "OFF to link as static library, ON as dynamic - on Windows the latter requires the *.dll to be copied next to the .exe (this is done in add_subdirectory)" ON)

if(NOT linkSociAsSharedLibrary)
    message(WARNING "For now SOCI can only be linked as a shared library: use \n\t-D linkSociAsSharedLibrary=ON\nor omit this flag")
endif()

include(${CMAKE_SOURCE_DIR}/CMakeUtils/FindOrFetch/FindOrFetchSoci.cmake)

get_property(importTargets3 DIRECTORY ${SOURCE_DIR} PROPERTY IMPORTED_TARGETS)
list(REMOVE_ITEM importTargets3 ${importTargets1} ${importTargets2})
message(STATUS "importTargets3: ${importTargets3}")

#[==================================================[
Link executable with libraries
#]==================================================]
if(linkSociAsSharedLibrary)

    target_link_libraries(targetDatabase 
        PRIVATE 
            MySql::MySql
            SOCI::soci_sqlite3
            SOCI::soci_mysql
            SOCI::soci_postgresql
            SOCI::soci_odbc
    )

else()

    target_link_libraries(targetDatabase 
        PRIVATE 
            MySql::MySql
            SOCI::soci_sqlite3_static
            SOCI::soci_mysql_static
            SOCI::soci_postgresql_static
            SOCI::soci_odbc_static
    )

endif()

#[==================================================[
On Windows copy *.dll needed at runtime by the .exe into the same directory as the .exe
#]==================================================]
option(isThereDllToLinkToDatabase "Switch OFF when not linking any DLLs, otherwise copy <empty> will fail!" ON)

if(linkSociAsSharedLibrary)
    set(isThereDllToLinkToDatabase ON)
else()
    set(isThereDllToLinkToDatabase OFF)
endif()

if(WIN32 AND isThereDllToLinkToDatabase)
        add_custom_command(TARGET targetDatabase POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "copy: $<TARGET_RUNTIME_DLLS:targetDatabase>"
            COMMAND ${CMAKE_COMMAND} -E echo "to:   $<TARGET_FILE_DIR:targetDatabase>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                    $<TARGET_RUNTIME_DLLS:targetDatabase> 
                    $<TARGET_FILE_DIR:targetDatabase>
            COMMAND_EXPAND_LISTS
        )
endif()

#[==================================================[
Run the executable 
#]==================================================]
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E echo "execute: $<TARGET_FILE:targetDatabase>"
    COMMAND $<TARGET_FILE:targetDatabase>
)
