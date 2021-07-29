cmake_minimum_required(VERSION 3.5.0)
project(grobot)

# build "libyaml: yaml.lib"
set(BUILD_TESTING FALSE) # Skip test building
add_subdirectory(libyaml)

# build "libgrobot: grobot.lib"
add_subdirectory(libgrobot)

# build "grobot_test executable"
add_subdirectory(grobot_test)

# build GR001 component
add_subdirectory(GR001Comp)

# build GR001 component
add_subdirectory(CmdInComp)
