
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
    ${includePath}/MiniImage.hpp
    ${includePath}/MiniPgm.hpp
    ${includePath}/MiniWindow.hpp
)

macro(create_executable target)
    add_executable(${target} ${includeFiles} ${CMAKE_CURRENT_SOURCE_DIR}/examples/${target}.cpp)
    target_include_directories(${target} PUBLIC "${includePath}")
endmacro()

create_executable(BlockBuilding3D)
create_executable(GaussianDistribution3D)
create_executable(ImgToPgm)
create_executable(Mandelbrot)
