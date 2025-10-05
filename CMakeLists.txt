cmake_minimum_required(VERSION 3.11)
project(SPN_DataStructures CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencies ---
include(FetchContent)

# Eigen (header-only)
FetchContent_Declare(
  Eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG 3.4.0
)
FetchContent_MakeAvailable(Eigen) # This sets eigen_SOURCE_DIR

# GoogleTest
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1 # A stable tag
)
FetchContent_MakeAvailable(googletest)


# --- Source files ---
set(APP_SOURCES
    src/main.cpp
    src/PetriNet.cpp
    src/ReachabilityGraph.cpp
    src/SPNAnalysis.cpp
    src/GraphGenerator.cpp
)

set(LIB_SOURCES
    src/PetriNet.cpp
    src/ReachabilityGraph.cpp
    src/SPNAnalysis.cpp
    src/GraphGenerator.cpp
)

set(TEST_SOURCES
    tests/test_main.cpp
    tests/test_PetriNet.cpp
    tests/test_ReachabilityGraph.cpp
    tests/test_SPNAnalysis.cpp
    tests/test_GraphGenerator.cpp
)

# --- Main Application ---
add_executable(spn_app ${APP_SOURCES})
target_include_directories(spn_app PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${eigen_SOURCE_DIR}
)


# --- Testing ---
enable_testing()
add_executable(run_tests ${TEST_SOURCES} ${LIB_SOURCES})
target_include_directories(run_tests PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${eigen_SOURCE_DIR}
)
target_link_libraries(run_tests PRIVATE gtest_main)

add_test(NAME unit_tests COMMAND run_tests)