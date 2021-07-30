cmake_minimum_required(VERSION 3.5.0)
project(grobot_test)

add_executable(grobot_test
    src/GROBO_Main.cpp
#    src/stdafx.cpp
)
target_include_directories(grobot_test
    PUBLIC ${libyaml_SOURCE_DIR}/include
    PUBLIC ${libgrobot_SOURCE_DIR}/include
    PUBLIC ${SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} libgrobot)