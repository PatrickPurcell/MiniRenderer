
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

macro(create_executable target)
    add_executable(${target} ${includeFiles} ${CMAKE_CURRENT_SOURCE_DIR}/${target}.cpp)
    target_include_directories(${target} PUBLIC "${includePath}")
endmacro()

create_executable(3DBlockBuilding)
create_executable(ImgToPgm)
