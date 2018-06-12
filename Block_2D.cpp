#include "Block_2D.hpp"

using namespace tetris_pdcurses;
using points_collection = Block_2D::points_collection;
using prefab_type = Block_2D::prefab_type;
using grid_type = Block_2D::grid_type;

const prefab_type Block_2D::prefab5x5( {u8"1234500000000000000000000000000000000000000000010000000000000000000000001100000000000",
                                        u8"678900000000R0000CC000Y00000B000W000GG00000000010001010000100010000110001000010000100", 
                                        u8"ABCDE0BBBB00R0000C0000YY000BB000WW00GG0000W0000R1001R1001R100111001R0000R0001R0000R10",
                                        u8"FGHIJ0000000RR000C00000Y000B0000W0000000000000010000000010000010000100001000110000000",
                                        u8"KLMNO00000000000000000000000000000000000000000000000000000000000000000000000000000000"});
//                                         ^-0-^^-1-^^-2-^^-3-^^-4-^^-5-^^-6-^^-7-^^-8-^^-9-^^-10^^-11^^-12^^-13^^-14^^-15^^-16^

Block_2D::Block_2D(std::size_t qSize, Point_2D start)
	: Block(Shape::Custom)
	, frame_grid(qSize)
	, frame_point(start)
{ }
Block_2D::Block_2D(Shape init_shape)
	: Block(init_shape)
	, frame_grid(setPattern(init_shape))
	, frame_point(-1, 3)
{ }
Block_2D::Block_2D(Shape init_shape, Point_2D spawn_pt)
	: Block(init_shape)
	, frame_grid(setPattern(init_shape))
	, frame_point(spawn_pt)
{ }
Block_2D::Block_2D(Point_2D start_pt, grid_type custom_grid)
	: Block(Shape::Custom)
	, frame_grid(custom_grid)
	, frame_point(start_pt)
{ }
std::pair<std::size_t, std::string> Block_2D::get_prefab(const std::size_t index, const prefab_type blocks) const
{
	auto size {blocks.size()};
	std::string pattern {""};
	for(std::string_view it: blocks )
	{
		pattern.append(it.substr(index * size, size) );
	}
	return {size, pattern};
}
std::pair<std::size_t, std::string> Block_2D::setPattern(const Shape shape)
{
	switch(shape)
	{
		case Shape::Line:
			return {get_prefab(1,prefab5x5)};
		case Shape::L:
			return {get_prefab(2,prefab5x5)};
		case Shape::rL:
			return {get_prefab(3,prefab5x5)};
		case Shape::N:
			return {get_prefab(4,prefab5x5)};
		case Shape::rN:
			return {get_prefab(5,prefab5x5)};
		case Shape::T:
			return {get_prefab(6,prefab5x5)};
		case Shape::Box:
			return {get_prefab(7,prefab5x5)};
		case Shape::Dot:
			return {get_prefab(8,prefab5x5)};
		case Shape::extBlock1:
			return {get_prefab(9,prefab5x5)};
		case Shape::extBlock2:
			return {get_prefab(10,prefab5x5)};
		case Shape::extBlock3:
			return {get_prefab(11,prefab5x5)};
		case Shape::extBlock4:
			return {get_prefab(12,prefab5x5)};
		case Shape::extBlock5:
			return {get_prefab(13,prefab5x5)};
		case Shape::extBlock6:
			return {get_prefab(14,prefab5x5)};
		case Shape::extBlock7:
			return {get_prefab(15,prefab5x5)};
		case Shape::extBlock8:
			return {get_prefab(16,prefab5x5)};
		case Shape::Test:
			return {get_prefab(0,prefab5x5)};
		default:
			return {get_prefab(6,prefab5x5)};
	}
}
bool Block_2D::isRotatable() const
{
	switch(unit_shape)
	{
		case Shape::Line:	// Rotateable shapes
		case Shape::L:
		case Shape::rL:
		case Shape::N:
		case Shape::rN:
		case Shape::T:
		case Shape::extBlock1:
		case Shape::extBlock2:
		case Shape::extBlock3:
		case Shape::extBlock4:
		case Shape::extBlock5:
		case Shape::extBlock6:
		case Shape::extBlock7:
		case Shape::extBlock8:
		case Shape::Test:
			return true;
		
		case Shape::Dot:	// Non-Rotateable shapes
		case Shape::Box:
		case Shape::Custom:
			return false;
			
		default:
			return false;
	}
	return false;
}
points_collection Block_2D::field_coordinates() const
{
	return field_coordinates(frame_point, frame_grid);
}
points_collection Block_2D::field_coordinates(const Point_2D start) const
{
	return field_coordinates(start, frame_grid);
}
points_collection Block_2D::field_coordinates(const grid_type grid) const
{
	return field_coordinates(frame_point, grid);
}
points_collection Block_2D::field_coordinates(const Point_2D start, const grid_type grid) const
{
	Block_2D::points_collection points;
	auto height {grid.height(int{})};
	for(int i{0}; i < height; ++i) {
		auto field {start};
		field.Y += i;
		for(auto ch: grid.row(i) )
		{
			if(ch == grid.empty_value()) 
			{
				field.X += 1;
				continue;
			}
			else {
				points.emplace_back(field); 
			}
			field.X += 1;
		}
	}
	return points;
}
grid_type Block_2D::rotate_grid(const Rotation rot_cmd) const
{
	return frame_grid.rotate(rot_cmd);
}
void Block_2D::apply(grid_type const& upd_grid)
{
	frame_grid = upd_grid;
}
void Block_2D::apply(const Point_2D approved_coordinates)
{
	frame_point = approved_coordinates;
}

Point_2D Block_2D::frame_coordinates() const
{
	return frame_point;
}
Point_2D Block_2D::to_local_coord(const Point_2D field) const
{
	auto local {field};
	local.Y -= frame_point.Y;
	local.X -= frame_point.X;
	return local;
}
std::pair<char, int> Block_2D::read_value(const Point_2D point, const bool convert_to_local) const
{
	if(convert_to_local){
		auto ch {frame_grid.at(to_local_coord(point) ) };
		return {ch, id() };
	}
	else {
		auto ch {frame_grid.at(point ) };
		return {ch, id() };
	}
	return { };
}
void Block_2D::clear_cell(const Point_2D point, const bool convert_to_local){
	if(convert_to_local){
		frame_grid.at( to_local_coord(point) ) = frame_grid.empty_value();
	}
	else{
		frame_grid.at( point ) = frame_grid.empty_value();
	}
}
std::vector<grid_type> Block_2D::separate_grids()
{
	std::vector<grid_type> grid_components; 
	auto split_map {frame_grid.value_points_map()};
	if(split_map.size() > 1)
	{
		while(not split_map.empty() )
		{
			auto uid {split_map.begin()->second }; // aquired first element id
			grid_components.emplace_back(frame_grid.height() ); 
			
			for(auto it{split_map.begin()}; it != split_map.end(); ++it) 
			{
				auto& [point, id] = *it;
				if( id == uid) { 
					grid_components.back().at(point) = frame_grid.at(point);
					if(split_map.erase(it) == split_map.end()) break; //it = split_map.erase(it);
				}
			}
		}
	}
	return grid_components;
}
void Block_2D::set_color(Color const color)
{
	
	auto color_ch {'0'};
	switch(color) 
	{
		case Color::Black:
			color_ch = frame_grid.empty_value();
			break;
		case Color::Red:
			color_ch = 'R';
			break;
		case Color::Green:
			color_ch = 'G';
			break;
		case Color::Blue:
			color_ch = 'B';
			break;
		case Color::Cyan:
			color_ch = 'C';
			break;
		case Color::Magenta:
			color_ch = 'M';
			break;
		case Color::Yellow:
			color_ch = 'Y';
			break;
		case Color::White:
			color_ch = 'W';
			break;
		case Color::Ghost:
			color_ch = 'O';
			break;
		default:
			color_ch = '1';
	}
	frame_grid.reset_data(color_ch);
}
void Block_2D::printGrid() {
	frame_grid.ios_print();
}