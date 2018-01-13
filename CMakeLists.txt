
# CMake configuration for MiniRenderer
cmake_minimum_required(VERSION 3.2)
project(MiniRenderer)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(includePath "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(includeFiles
    ${includePath}/Defines.hpp
    ${includePath}/MiniGLM.hpp
    ${includePath}/MiniGLM_ex.hpp
    ${includePath}/MiniRenderer.hpp
    ${includePath}/Pgm.hpp
)

add_executable(MiniWindow ${includeFiles} ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp)
target_include_directories(MiniWindow PUBLIC "${includePath}")

add_executable(3DBlockBuilding ${includeFiles} ${CMAKE_CURRENT_SOURCE_DIR}/3DBlockBuilding.cpp)
target_include_directories(3DBlockBuilding PUBLIC "${includePath}")
