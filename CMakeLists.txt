cmake_minimum_required(VERSION 3.17)

project(Shameless_Minecraft_Clone)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_link_options("-lglfw" "-lGL" "-ldl" "-lm" "-lGLEW")

add_executable(run ${SOURCES})