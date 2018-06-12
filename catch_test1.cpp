#include <string>
#include <iostream>

#include "catch.hpp"
#include "curses.h"
#include "Point_2D.hpp"
#include "Grid_2D.hpp"
#include "Block_2D.hpp"

using namespace tetris_pdcurses;

TEST_CASE("Creating Point_2D object", "[Point_2D]")
{	
	Point_2D point1(2, 42);
	REQUIRE(point1.Y == 2);
	REQUIRE(point1.X == 42);
	
	SECTION("checking operator==")
	{
		Point_2D point2(2, 42);
		REQUIRE(point1 == point2);
		
		SECTION("checking setter")
		{
			point2.set(-22, 256);
			REQUIRE(point2.Y == -22);
			REQUIRE(point2.X == 256);
		}
	}
	SECTION("checking operator<")
	{
		REQUIRE( Point_2D(0, 1) < Point_2D(1, 1) );
		REQUIRE( Point_2D(2, 1) < Point_2D(3, -55) );
		REQUIRE( Point_2D(-55, 42) < Point_2D(1, 0) );
		
		REQUIRE_FALSE( Point_2D(0, 0) < Point_2D(0, 0));
		REQUIRE_FALSE( Point_2D(1, 1) < Point_2D(1, 1));
		REQUIRE_FALSE( Point_2D(-1, -1) < Point_2D(-1, -1));
		REQUIRE_FALSE( Point_2D(4, 1) < Point_2D(3, 2));
	}
}

TEST_CASE("Creating Grid_2D object", "[Grid_2D]") 
{	
	Grid_2D<> grid1(5);
	Grid_2D<> grid2(5);
	
	SECTION("checking .at()")
	{	
		REQUIRE(grid1.at(Point_2D(0, 0))   == '0' );
		REQUIRE(grid1.at(Point_2D(-1, 5))  == '-' );
	}
	SECTION("checking .row()") 
	{
		std::string temp1 {grid1.row(0)};
		REQUIRE(temp1 == std::string("00000"));
	}
	SECTION("checking .column()") 
	{
		std::string temp2 {grid1.column(0)};
		REQUIRE(temp2 == std::string("00000"));
	}
	SECTION("checking .rcolumn()") 
	{
		std::string temp3 {grid1.rcolumn(0)};
		REQUIRE(temp3 == std::string("00000"));
	}
	SECTION("checking .isValid()")
	{
		REQUIRE(grid1.isValid(Point_2D(0, 5)) == false);
		REQUIRE(grid1.isValid(Point_2D(5, 0)) == false);
		REQUIRE(grid1.isValid(Point_2D(-1, 6)) == false);
		REQUIRE(grid1.isValid(Point_2D(-1, -3)) == false);
	}
	SECTION("checking .put()")
	{
		Grid_2D grid3(3);
		std::pair<Point_2D, char> p {Point_2D(1, 1), 'H'};
		grid3.put(p);
		REQUIRE(grid3.at(Point_2D(1,1)) == 'H');
	}
	SECTION("checking .rotate()")
	{
		Grid_2D grid(5);
		grid.put(0, 0,'R');
		grid.put(4, 4,'G');
		grid.put(4, 0,'B');
		
		auto rotated_grid {grid.rotate(Rotation::Right_p90) };
		REQUIRE(rotated_grid.at(Point_2D(0, 0)) == 'B');
		REQUIRE(rotated_grid.at(Point_2D(4, 0)) == 'G');
		REQUIRE(rotated_grid.at(Point_2D(0, 4)) == 'R');
		REQUIRE(rotated_grid.at(Point_2D(3, 3)) == '0');
	}
	SECTION("checking .value_points_map() - 1")
	{
		Grid_2D grid(5);
		//00000 //00000
		//00G0E //00102
		//Z0R00 //30100
		//00000 //00000
		//00YY0 //00440
		grid.put(1, 2,'G');
		grid.put(1, 4,'E');
		grid.put(2, 0,'Z');
		grid.put(2, 2,'R');
		grid.put(3, 2,'0');
		grid.put(4, 2,'Y');
		grid.put(4, 3,'Y');
		
		
		auto split_map = grid.value_points_map();
		//for(auto& [point, id]: split_map) {
		//	std::cout << "[" << point.Y << " " << point.X << "]" << id << '\n';
		//}
		
		REQUIRE(split_map.size() == 6);
		CHECK(split_map.at(Point_2D{1, 2}) == 1);
		CHECK(split_map.at(Point_2D{1, 4}) == 2);
		CHECK(split_map.at(Point_2D{2, 2}) == 1);
		CHECK(split_map.at(Point_2D{4, 2}) == 4);
		CHECK(split_map.at(Point_2D{4, 3}) == 4);
		CHECK(split_map.at(Point_2D{2, 0}) == 3);
	}
	SECTION("checking .value_points_map() - 2")
	{
		Grid_2D grid(5);
		//Z0000 //10000
		//00GG0 //00220
		//00R00 //00200
		//0Y0FE //04044
		//YYFF0 //44440
		grid.put(0, 0,'Z');
		grid.put(1, 2,'G'); 
		grid.put(1, 3,'G'); 
		grid.put(2, 2,'R');
		grid.put(3, 1,'Y');
		grid.put(3, 3,'F');
		grid.put(3, 4,'E');
		grid.put(4, 0,'Y');
		grid.put(4, 1,'Y');
		grid.put(4, 2,'F');
		grid.put(4, 3,'F');
		
		auto split_map = grid.value_points_map();

		REQUIRE(split_map.size() == 11);
		CHECK(split_map.at(Point_2D{0, 0}) == 1);
		CHECK(split_map.at(Point_2D{1, 2}) == 2);
		CHECK(split_map.at(Point_2D{1, 3}) == 2);
		CHECK(split_map.at(Point_2D{2, 2}) == 2);
		CHECK(split_map.at(Point_2D{3, 1}) == 4);
		CHECK(split_map.at(Point_2D{3, 3}) == 4);
		CHECK(split_map.at(Point_2D{3, 4}) == 4);
		CHECK(split_map.at(Point_2D{4, 0}) == 4);
		CHECK(split_map.at(Point_2D{4, 1}) == 4);
		CHECK(split_map.at(Point_2D{4, 2}) == 4);
		CHECK(split_map.at(Point_2D{4, 3}) == 4);
	}
	SECTION("checking .value_points_map() - 3")
	{
		Grid_2D grid(5);
		grid.put(1, 2,'W');
		grid.put(2, 2,'W'); 
		grid.put(4, 2,'W');
		auto split_map = grid.value_points_map();

		REQUIRE(split_map.size() == 3);
		CHECK(split_map.at(Point_2D{1, 2}) == 1);
		CHECK(split_map.at(Point_2D{2, 2}) == 1);
		CHECK(split_map.at(Point_2D{4, 2}) == 2);
	}
}

TEST_CASE("Creating Block_2D object", "[Block_2D]") {

	Block_2D block1(Shape::T);
	Block_2D block2(Shape::L);
	
	SECTION("checking .read_value()")
	{
		auto [letter, block_id] = block2.read_value(Point_2D(2, 2), false);
		
		REQUIRE( block_id == 2);
		REQUIRE( letter == 'R');
	}
	SECTION("checking .clear_cell()")
	{
		block1.clear_cell(Point_2D(2, 2), false);
		auto [letter, block_id] = block1.read_value(Point_2D(2, 2), false);
		
		REQUIRE(letter == '0');
	}
	SECTION("checking .separate_grids() - 1")
	{
		block1.clear_cell(Point_2D(2, 2), false);
		auto grids = block1.separate_grids();
		//block1.printGrid();
		REQUIRE(grids.size() == 3);
	}
	SECTION("checking .separate_grids() - 2")
	{
		Block_2D block(Shape::Line);
		block.apply(block.rotate_grid(Rotation::Right_p90));
		block.clear_cell(Point_2D(3, 2), false);
		//block.printGrid();
		auto grids = block.separate_grids();
		REQUIRE(grids.size() == 2);
	}
	SECTION("checking .separate_grids() - 3")
	{
		Block_2D block(Shape::N);
		block.apply(block.rotate_grid(Rotation::Right_p90));
		block.apply(block.rotate_grid(Rotation::Right_p90));
		block.clear_cell(Point_2D(2, 1), false);
		block.clear_cell(Point_2D(2, 2), false);
		block.printGrid();
		auto grids = block.separate_grids();
		REQUIRE(grids.size() == 2);
	}
}

// catch2test.exe --reporter compact --success
