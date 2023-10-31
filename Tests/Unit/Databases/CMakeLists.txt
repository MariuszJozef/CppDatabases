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
On Windows copy *.dll needed at runtime by the .exe into the same directory as the .exe
#]==================================================]
option(isThereDllToLinkToUnitTestDatabase "Switch OFF when not linking any DLLs, otherwise copy <empty> will fail!" OFF)

if(WIN32 AND isThereDllToLinkToUnitTestDatabase)
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
Link executable with found/fetched libraries
#]==================================================]
target_link_libraries(targetUnitTestDatabase 
    PRIVATE 
        GTest::gtest_main
        GTest::gmock_main
)

#[==================================================[
Run tests
#]==================================================]
gtest_discover_tests(targetUnitTestDatabase)
