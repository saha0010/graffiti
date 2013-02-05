# --------------------------------------------------------------------------
# $File: //depot/vlg/Demos/GLSL/gooch/Aufgabenstellung/CMakeLists.txt $
# $Revision: #1 $
# $Date: 2012/04/19 $
# --------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8)
project (Virtual_Graffiti)

# Variable setzen für die verschiedenen Namen der OpenGL-Libs
INCLUDE(ogllibs.txt)
INCLUDE(buildtype.txt)
INCLUDE(CMakeVRPN.txt)

make_directory(${CMAKE_CURRENT_BINARY_DIR}/textures)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/asphalt_1.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/mauer_1.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/holzwand.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/wand_backstein_2.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/wand_backstein_3.bmp ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/credits.jpg ${CMAKE_CURRENT_BINARY_DIR}/textures COPYONLY)
make_directory(${CMAKE_CURRENT_BINARY_DIR}/stamps)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/stamps/fhlogo.bmp ${CMAKE_CURRENT_BINARY_DIR}/stamps COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/yellow.vsh ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

make_directory(${CMAKE_CURRENT_BINARY_DIR}/savedPictures)


# Das ausführbare Programm
add_executable (Graffiti graffiti.cpp GraffitiEngine.cpp GraffitiEngine.h 
                PolyLine.cpp PolyLine.h
                PolyLineView.cpp PolyLineView.h 
				Wall.h Wall.cpp 
				WallView.h WallView.cpp
				CircleLineView.cpp CircleLineView.h
				Stamp.h Stamp.cpp
				StampView.h StampView.cpp
				Circle.h Circle.cpp
				CircleView.h CircleView.cpp
				Color.h Color.cpp
				Shape.h Shape.cpp
				Rectangle.h Rectangle.cpp
				Triangle.h Triangle.cpp
				TriangleView.h TriangleView.cpp
				Line.h Line.cpp
				)
TARGET_LINK_LIBRARIES(Graffiti  vlgGlut vlg vlgVRPN ${GLUT_LIB} ${GLU_LIB} ${GL_LIB} ${VRPN_LIB} vrpn)
