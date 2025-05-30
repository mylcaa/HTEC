# make a build folder and in it run the following:
#cmake -DCMAKE_MAKE_PROGRAM="C:/MinGW/bin/mingw32-make.exe" -G "MinGW Makefiles" ..
#build with C:/MinGW/bin/mingw32-make.exe in the build folder
#run the file from GIT BASH - cmd doesn't recognise ./ as a command
#or run it from the cmd prompt with just the [executable_name].exe typed in 
cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")

project(
	LinkedList
	LANGUAGES CXX
)

enable_testing() #to  discover tests in test explorer 
add_subdirectory(googletest) # add googletest subdirectory
include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(mytests mytests.cpp) # add this executable

target_link_libraries(mytests PRIVATE gtest) # link google test to this executable

include(GoogleTest)
gtest_discover_tests(mytests) # discovers tests by asking the compiled test executable to enumerate its tests
