cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Breakout)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(Breakout main.cpp)

# Link the SFML libraries
target_link_libraries(Breakout sfml-graphics sfml-window sfml-system)