cmake_minimum_required(VERSION 3.28)
project(SPKCard LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(truthtable main.cpp)
target_compile_features(truthtable PRIVATE cxx_std_17)
target_link_libraries(truthtable PRIVATE SFML::Graphics)
target_link_libraries(truthtable PRIVATE SFML::Audio)
target_link_libraries(truthtable PRIVATE SFML::Window)
target_include_directories(truthtable PRIVATE ${CMAKE_SOURCE_DIR}/src)