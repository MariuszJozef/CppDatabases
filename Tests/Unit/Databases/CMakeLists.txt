#[==================================================[
UnitTestDatabase
#]==================================================]
add_executable(targetUnitTestDatabase)

target_include_directories(targetUnitTestDatabase
    PRIVATE
        ../../../Code/Databases/hdr
        ../../../Code/Databases/include
        ../../../Mock/Databases/hdr
        hdr
)

target_sources(targetUnitTestDatabase
    PRIVATE
        ../../../Code/Databases/include/Common.hpp
        ../../../Code/Databases/include/DatabaseApi.hpp
        ../../../Code/Databases/src/DatabaseApi.cpp
        ../../../Code/Databases/hdr/Database.hpp
        ../../../Code/Databases/src/Database.cpp
        ../../../Code/Databases/hdr/DatabaseSqlite.hpp
        ../../../Code/Databases/src/DatabaseSqlite.cpp
        ../../../Code/Databases/hdr/DatabaseMySql.hpp
        ../../../Code/Databases/src/DatabaseMySql.cpp
        ../../../Code/Databases/hdr/DatabasePostgreSql.hpp
        ../../../Code/Databases/src/DatabasePostgreSql.cpp
        ../../../Code/Databases/hdr/DatabaseMsSqlServer.hpp
        ../../../Code/Databases/src/DatabaseMsSqlServer.cpp
        ../../../Code/Databases/hdr/TableRecords.hpp
        ../../../Code/Databases/src/TableRecords.cpp
        ../../../Code/Databases/hdr/ConvertRecordTypes.hpp
        ../../../Mock/Databases/hdr/IRealEntity.hpp
        ../../../Mock/Databases/hdr/MockEntity.hpp
        ../../../Mock/Databases/src/TestMockEntity.cpp
        src/UnitTestDatabase.cpp
)

set_target_properties(targetUnitTestDatabase
    PROPERTIES
        OUTPUT_NAME                         UnitTestDatabase
        EXPORT_NAME                         UnitTestDatabase
        DEBUG_POSTFIX                       "_d"
        RUNTIME_OUTPUT_DIRECTORY            ${CMAKE_BINARY_DIR}/buildOut/UnitTestDatabases/bin/$<CONFIG>
        PDB_OUTPUT_DIRECTORY                ${CMAKE_BINARY_DIR}/buildOut/UnitTestDatabases/pdb/$<CONFIG>
        RUNTIME_OUTPUT_DIRECTORY_<Config>   ${RUNTIME_OUTPUT_DIRECTORY}
        PDB_OUTPUT_DIRECTORY_<Config>       ${PDB_OUTPUT_DIRECTORY}
)

target_compile_features(targetUnitTestDatabase
    PRIVATE
        cxx_std_20
)

if(MSVC)

    target_compile_options(targetUnitTestDatabase 
        PRIVATE
            /EHsc
            /W2
            # /Wall
    )

else()

    target_compile_options(targetUnitTestDatabase 
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

    target_link_libraries(targetUnitTestDatabase 
        PRIVATE 
            GTest::gtest_main
            GTest::gmock_main
            MySql::MySql
            SOCI::soci_sqlite3
            SOCI::soci_mysql
            SOCI::soci_postgresql
            SOCI::soci_odbc
    )

else()

    target_link_libraries(targetUnitTestDatabase 
        PRIVATE 
            GTest::gtest_main
            GTest::gmock_main
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
        add_custom_command(TARGET targetUnitTestDatabase POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "copy: $<TARGET_RUNTIME_DLLS:targetUnitTestDatabase>"
            COMMAND ${CMAKE_COMMAND} -E echo "to:   $<TARGET_FILE_DIR:targetUnitTestDatabase>"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different 
                    $<TARGET_RUNTIME_DLLS:targetUnitTestDatabase> 
                    $<TARGET_FILE_DIR:targetUnitTestDatabase>
            COMMAND_EXPAND_LISTS
        )
endif()

#[==================================================[
Run tests
#]==================================================]
gtest_discover_tests(targetUnitTestDatabase)
