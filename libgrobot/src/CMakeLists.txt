cmake_minimum_required(VERSION 3.5.0)

# Build "grobot.lib"
add_library(libgrobot
  STATIC
    GROBO.cpp
    CUtils.cpp
    SerialPort.cpp
    YamlParser.cpp
    SerialRobot.cpp
    stdafx.cpp
  )
target_include_directories(libgrobot
  PUBLIC ${libgrobot_SOURCE_DIR}/include
  PUBLIC ${libyaml_SOURCE_DIR}/include
)
# link yaml.lib under libyaml
target_link_libraries(${PROJECT_NAME} yaml)
