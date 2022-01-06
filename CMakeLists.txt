# CMakeList.txt : CMake project for TestNana, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.0)

project ("finalProject_game")


add_definitions(-D_SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING)
# Add source to this project's executable.
add_executable (finalProject_game "finalProject_game.cpp" "finalProject_game.h" "card.h" "game.h" "records.h")

#This line fixes the /MDd problem on slide #9
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /NANA_ENABLE_AUDIO")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /NANA_ENABLE_AUDIO")

target_include_directories(finalProject_game PUBLIC "C:\\Users\\novac\\source\\repos\\finalProject_game\\nana_1.7.4\\nana\\include")
target_link_directories(finalProject_game PUBLIC "C:\\Users\\novac\\source\\repos\\finalProject_game\\nana_1.7.4\\nana\\build\\bin")
target_link_libraries(finalProject_game "nana_v142_Debug_x64")
add_definitions(-DNANA_ENABLE_AUDIO)