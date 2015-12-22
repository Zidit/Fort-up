cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_COMPILER g++)
project(fort_up)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules/)

find_package(SFML 2 COMPONENTS graphics audio window network system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

find_package( SFGUI REQUIRED )
include_directories( ${SFGUI_INCLUDE_DIR} )

find_package( GLM REQUIRED )
include_directories( ${GLM_INCLUDE_DIRS} )

find_package( OpenGL REQUIRED )
find_package( GLEW REQUIRED )
include_directories( ${GLEW_INCLUDE_DIR} )

ADD_SUBDIRECTORY(polyvox)
include_directories(${CMAKE_SOURCE_DIR}/polyvox/library/PolyVoxCore/include)
set(POLYVOX_LIBRARY PolyVoxCore PolyVoxUtil)

include_directories( ${CMAKE_SOURCE_DIR}/src/ )
set(LIBS ${SFML_LIBRARIES} ${SFGUI_LIBRARY} ${POLYVOX_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})
add_definitions(-std=c++0x -g)
add_definitions(-DGLM_FORCE_RADIANS)

FILE(GLOB_RECURSE sources src/*)
add_executable(fort_up ${sources})
target_link_libraries(fort_up ${LIBS})

