cmake_minimum_required (VERSION 3.13)

project(Decode62256Analyzer)

add_definitions( -DLOGIC2 )

# enable generation of compile_commands.json, helpful for IDEs to locate include files.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# custom CMake Modules are located in the cmake directory.
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(ExternalAnalyzerSDK)

set(SOURCES 
src/Decode62256Analyzer.cpp
src/Decode62256Analyzer.h
src/Decode62256AnalyzerResults.cpp
src/Decode62256AnalyzerResults.h
src/Decode62256AnalyzerSettings.cpp
src/Decode62256AnalyzerSettings.h
src/Decode62256SimulationDataGenerator.cpp
src/Decode62256SimulationDataGenerator.h
)

add_analyzer_plugin(${PROJECT_NAME} SOURCES ${SOURCES})
