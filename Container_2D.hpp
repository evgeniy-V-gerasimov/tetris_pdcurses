#ifndef CONTAINER_2D_HPP
#define CONTAINER_2D_HPP

#include <cstddef>
#include <string_view>
#include <vector>
#include <map>
#include <tuple>
#include <queue>
#include <variant>

#include "Container.hpp"
#include "Block_2D.hpp"
#include "Point_2D.hpp"
#include "Grid_2D.hpp"

namespace tetris_pdcurses {

class Container_2D: public Container {

public:
	using grid_value_type = std::pair<char, int>;
	using grid_type = Grid_2D<std::vector<grid_value_type> >;
	using points_collection = Block_2D::points_collection; // std::vector<std::pair<Point_2D, char>>
	using block_iterator = std::vector<Block_2D>::iterator;
	using block_id_set = std::set<std::size_t>;
	
	class Event {
	public:
		struct BlockLanded{};
		struct CtrlBlockLanded{};
		struct Sanitize{};
	
		using ContainerEvent = std::variant<BlockLanded,
											CtrlBlockLanded,
											Sanitize>;
		ContainerEvent name;
	};
	
	explicit Container_2D(std::size_t, std::size_t);
	~Container_2D() = default;
	Container_2D& operator=(const Container_2D&) = default;

	bool add_block(const Shape);
	bool move_block(const Direction);
	bool rotate_block(const Rotation);
	void drop_block();
	void split_blocks(block_id_set );
	void gravity();
	void sanitizeRemoved();
	block_id_set erase_full_lines();
	
	std::size_t blocks_count() const;
	std::string row_to_str(const int) const;
	int height() const;
	int width() const;
	
	void pushEvent(const Event&);
	void popEvent();
	bool hasEvents();
	Event::ContainerEvent getEvent();
private:
	grid_type field_grid;
	Point_2D spawn_point;
	std::vector<Block_2D> BlockData; 
	std::queue<Event> events;
	
	bool action(const Rotation, const Direction, Block_2D& );
	void remove_from_field(points_collection);
	bool projection_to_field(points_collection);
	void apply_to_field(points_collection, Block_2D&);
	
	Block_2D& ref_controlled_block();
	bool isBurnable_row(std::size_t);
	void remove_block_cells(std::multimap<std::size_t, Point_2D>);
	block_iterator find_block_with_id(const std::size_t);
	
};

} //namespace tetris_pdcurses
#endif // CONTAINER_2D_HPP