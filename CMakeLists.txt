cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Set the project name
project(Breakout)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(Breakout src/main.cpp)

# Link the SFML libraries
target_link_libraries(Breakout sfml-graphics sfml-window sfml-system)

# Enable testing
enable_testing()

# Add the Google Test framework
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# Include directories for tests
include_directories(${PROJECT_SOURCE_DIR}/src)
# Add the test executable
add_executable(runTests 
    Tests/test_SceneObjects.cpp
    Tests/test_Collision.cpp
)

# Link the Google Test libraries
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
# Link the SFML libraries
target_link_libraries(runTests sfml-graphics sfml-window sfml-system)

# Add a test
add_test(NAME runTests COMMAND runTests)
