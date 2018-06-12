#ifndef BLOCK_2D_HPP
#define BLOCK_2D_HPP

#include <vector>
#include <set>
#include <cstddef>
#include <tuple>
#include <functional>

#include "Block.hpp"
#include "Point_2D.hpp"
#include "Grid_2D.hpp"
#include "tetris_enums.hpp"

namespace tetris_pdcurses {

class Block_2D: public Block {
public:
	using prefab_type = std::vector<std::string>;
	using points_collection = std::vector<Point_2D>;
	using grid_value_type = char;
	using grid_type = Grid_2D<std::string>;
	
	static const prefab_type prefab5x5; // Collection of blocks in a human-readable form
	Block_2D(Shape);
	Block_2D(Shape, Point_2D);
	Block_2D(std::size_t, Point_2D);
	Block_2D(Point_2D, grid_type);
	~Block_2D() = default;
	Block_2D& operator=(const Block_2D&) = default;
	
	points_collection field_coordinates() const;
	points_collection field_coordinates(const Point_2D) const;
	points_collection field_coordinates(const grid_type) const;
	points_collection field_coordinates(const Point_2D, const grid_type) const;
	
	bool isRotatable() const;
	grid_type rotate_grid(const Rotation) const;
	
	void apply(grid_type const&);
	void apply(const Point_2D);
	
	Point_2D frame_coordinates() const;
	std::pair<char, int> read_value(const Point_2D, const bool convert_to_local = true) const;
	void clear_cell(const Point_2D, const bool  = true);
	std::vector<grid_type> separate_grids();
	void set_color(const Color);
	void printGrid();
private:
	grid_type frame_grid;
	Point_2D frame_point;
	std::pair<std::size_t, std::string> get_prefab(const std::size_t, const prefab_type) const;
	Point_2D to_local_coord(const Point_2D) const;
	std::pair<std::size_t, std::string> setPattern(const Shape);
};

} //namespace tetris_pdcurses
#endif // BLOCK_2D_HPP