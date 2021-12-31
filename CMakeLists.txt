cmake_minimum_required(VERSION 3.21)
project(billiards3D)

set(CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(billiards3D main.cpp)
file(GLOB source_files CONFIGURE_DEPENDS "Shot.wav" "hit.wav" "shot.wav")
target_link_libraries(billiards3D -lOpenGL32 -lfreeGLUT -lGLU32 winMM.Lib)
