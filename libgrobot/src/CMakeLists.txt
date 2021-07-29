cmake_minimum_required(VERSION 3.5.0)

# Build "grobot.lib"
add_definitions(-DGR001_EXPORTS)
add_library(libgrobot
  STATIC
    stdafx.cpp
    CUtils.cpp
    YamlParser.cpp
    SerialPort.cpp
    SerialRobot.cpp
    GROBO.cpp
  )
target_include_directories(libgrobot
  PUBLIC ${libgrobot_SOURCE_DIR}/include
  PUBLIC ${libyaml_SOURCE_DIR}/include
)
# link yaml.lib under libyaml
target_link_libraries(${PROJECT_NAME} yaml)
