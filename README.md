# SOCI backend integrated with ImGui frontend to perform CRUD operations on various databases: SQLite3, MySQL, PostgreSql, MS SQL Server

## Project structure

## Commands to build, run, and test the program

```
git clone --depth 1 https://github.com/MariuszJozef/DatabaseGuiIntegration.git
cd DatabaseGuiIntegration
```

Start MySql and PostgreSql servers, make sure their status is "active (running)":
```
systemctl start mysqld
systemctl status mysqld
```

![ScreenShot1](ScreenShots/ScreenShot1.png)

```
systemctl start postgresql
systemctl status postgresql
```

![ScreenShot2](ScreenShots/ScreenShot2.png)

At the end of running the program remember to switch off database servers:
```
systemctl stop mysqld
systemctl stop postgresql
```

**N.B.**

For now SOCI can only be linked as a shared library, there are link errors when linking it statically, therefore **do not** set the flag:
`-D linkSociAsSharedLibrary=OFF`; it is omitted below and defaults to `ON`.

```
cmake --preset NMake-Msvc-Debug
cmake --build --preset NMake-Msvc-Debug
cmake --build --preset NMake-Msvc-Debug --target run
cmake --build --preset NMake-Msvc-Debug --target runUnitTest
cmake --build --preset NMake-Msvc-Debug --target runIntegrationTest
cmake --build --preset NMake-Msvc-Debug --target runAllTests
cmake --build --preset NMake-Msvc-Debug --target runAll
ctest --preset NMake-Msvc-Debug --output-on-failure
```

```
cmake --preset Make-Gnu-Debug
cmake --build --preset Make-Gnu-Debug
cmake --build --preset Make-Gnu-Debug --target run
cmake --build --preset Make-Gnu-Debug --target runUnitTest
cmake --build --preset Make-Gnu-Debug --target runIntegrationTest
cmake --build --preset Make-Gnu-Debug --target runAllTests
cmake --build --preset Make-Gnu-Debug --target runAll
ctest --preset Make-Gnu-Debug --output-on-failure
```

```
cmake --preset Make-Clang-Debug
cmake --build --preset Make-Clang-Debug
cmake --build --preset Make-Clang-Debug --target run
cmake --build --preset Make-Clang-Debug --target runUnitTest
cmake --build --preset Make-Clang-Debug --target runIntegrationTest
cmake --build --preset Make-Clang-Debug --target runAllTests
cmake --build --preset Make-Clang-Debug --target runAll
ctest --preset Make-Clang-Debug --output-on-failure
```

## C++ CRUD operations into MySql database are confirmed

NULL values are read/write-able via std::optional (in the third table).

![ScreenShot3a](ScreenShots/ScreenShot3a.png)
![ScreenShot3b](ScreenShots/ScreenShot3b.png)
![ScreenShot3c](ScreenShots/ScreenShot3c.png)


## C++ CRUD operations into PostgreSql database are confirmed

![ScreenShot4a](ScreenShots/ScreenShot4a.png)
![ScreenShot4b](ScreenShots/ScreenShot4b.png)
![ScreenShot4c](ScreenShots/ScreenShot4c.png)

## C++ CRUD operations into SQLite3 database are confirmed

![ScreenShot5a](ScreenShots/ScreenShot5a.png)
![ScreenShot5b](ScreenShots/ScreenShot5b.png)
![ScreenShot5c](ScreenShots/ScreenShot5c.png)
