project(main)

cmake_minimum_required(VERSION 2.8)
set(Boost_INCLUDE_DIR "c:/mingw/boost32/include/boost-1_64/")	# Directory containing Boost headers (32bit)
set(Boost_LIBRARY_DIR "c:/mingw/boost32/lib/") 					# Default value for Boost_LIBRARY_DIR_RELEASE and Boost_LIBRARY_DIR_DEBUG.
set( Boost_USE_STATIC_LIBS ON ) # !uses .a files, NOT .dll's
set( Boost_USE_MULTITHREADED ON ) # Set to OFF to use the non-multithreaded libraries ('mt' tag).  Default is ON.

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O2 -static-libgcc -static-libstdc++ -static -lpthread") 

set(PDCURSES_INCLUDE_DIR "c:/mingw/pdcurses32/")
set(CATCH_INCLUDE_DIR "c:/mingw/catch2/single_include/")
set(PDCURSES_SHARED_LIB "c:/mingw/pdcurses32/win32/pdcurses.dll") #set(PDCURSES_STATIC_LIB c:/mingw/pdcurses32/win32/libpdcurses.a )

find_package( Boost 1.64.0 REQUIRED QUIET 
			COMPONENTS random system )				#  Boost libraries by their canonical name
	
if(Boost_FOUND)										# True if headers and requested libraries were found
	message(STATUS "<> [${PROJECT_NAME}]")			# 
	message(STATUS "<> ${Boost_INCLUDE_DIRS}") 	# Boost include directories
	message(STATUS "<> ${Boost_LIBRARY_DIRS}") 	# Link directories for Boost libraries
	message(STATUS "<> ${Boost_LIBRARIES}")
	message(STATUS "<> ${CATCH_INCLUDE_DIR}")
	message(STATUS "<> ${PDCURSES_INCLUDE_DIR}")
include_directories (${Boost_INCLUDE_DIRS} ${PDCURSES_INCLUDE_DIR} ${CATCH_INCLUDE_DIR}) 

add_executable(${PROJECT_NAME} main.cpp Block.cpp Block.hpp Block_2D.cpp Block_2D.hpp Container.cpp Container.hpp Container_2D.cpp Container_2D.hpp Grid_2D.hpp Grid_2D.cpp IGame.hpp tetris_enums.hpp Point_2D.cpp Point_2D.hpp ITetris.hpp TetrisClassicPDC.cpp TetrisClassicPDC.hpp)
add_executable(catch2test catch_test_main.cpp catch_test1.cpp Block.cpp Block.hpp Block_2D.cpp Block_2D.hpp Container.cpp Container.hpp Container_2D.cpp Container_2D.hpp Grid_2D.hpp Grid_2D.cpp IGame.hpp tetris_enums.hpp Point_2D.cpp Point_2D.hpp ITetris.hpp TetrisClassicPDC.cpp TetrisClassicPDC.hpp ${CATCH_INCLUDE_DIR}/catch.hpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${PDCURSES_SHARED_LIB}) 
target_link_libraries(catch2test ${Boost_LIBRARIES} ${PDCURSES_SHARED_LIB})
endif()
