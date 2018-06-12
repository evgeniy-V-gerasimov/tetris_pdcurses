#include "Container_2D.hpp"

using namespace tetris_pdcurses;
using grid_value_type = Container_2D::grid_value_type;
using block_iterator = Container_2D::block_iterator;
using block_id_set = Container_2D::block_id_set;

Container_2D::Container_2D(std::size_t height, std::size_t width) 
	: Container()
	, field_grid(height, width ) 
	, spawn_point(0, 3)
{	
	BlockData.reserve(100);
}
void Container_2D::gravity() {
	for(auto& block: BlockData) 
	{
		auto move_result = action(Rotation::None, Direction::Down, block);
		Event event;
		if(block.isFalling() && !move_result)
		{
			block.mLanded();
			event.name = Container_2D::Event::BlockLanded();
			pushEvent(event);
			continue;
		}
		if(block.isControlled() && !move_result)
		{
			block.mLanded();
			event.name = Container_2D::Event::CtrlBlockLanded();
			pushEvent(event);
			continue;
		}
		if(block.isLanded() && move_result)
		{
			block.mFree();
			continue;
		}
		if(block.isRemoved() )
		{
			event.name = Container_2D::Event::Sanitize();
			pushEvent(event);
		}
	}
}
void Container_2D::sanitizeRemoved() {
	for(auto it = BlockData.begin(); it != BlockData.end(); ++it) 
	{
		if(it->isRemoved() )
		{
			it = BlockData.erase(it);
		}
	}
}
bool Container_2D::add_block(const Shape shape)
{
	Block_2D spawning_block(shape, spawn_point);
	auto block_current_pos {spawning_block.field_coordinates() };
	
	if( projection_to_field(block_current_pos) )  
	{
		apply_to_field(block_current_pos, spawning_block);
		BlockData.emplace_back(spawning_block);
		return true;
	}
	else {
		return false;
	}
}
bool Container_2D::action(const Rotation rot_cmd, const Direction dir_cmd, Block_2D& block)
{
	auto block_current_pos {block.field_coordinates() };
	if(block_current_pos.size() == 0){ // if block has no value points, mark it for removal
		block.mRemoved();
		return false;
	}
	auto f_act = [&](auto target)
	{
		auto block_new_pos {block.field_coordinates(target) };
		remove_from_field(block_current_pos);
		if(projection_to_field(block_new_pos) ) 
		{
			block.apply(target);
			apply_to_field(block_new_pos, block);
			return true;
		}
		else {
			apply_to_field(block_current_pos, block);
		}
		return false;
	};
	if(rot_cmd != Rotation::None){
		if(not block.isRotatable() )
			return false;
		return f_act(block.rotate_grid(rot_cmd) );
	}
	if(dir_cmd != Direction::None){
		return f_act(block.frame_coordinates().shift(dir_cmd, 1) );
	}
	return false;
}
bool Container_2D::move_block(const Direction dir_cmd){
	auto& block {ref_controlled_block() };
	return action(Rotation::None, dir_cmd, block);
}
bool Container_2D::rotate_block(const Rotation rot_cmd){
	auto& block {ref_controlled_block() };
	return action(rot_cmd, Direction::None, block); 
}
void Container_2D::drop_block() 
{
	auto& block {ref_controlled_block() };
	while(action(Rotation::None, Direction::Down, block) ) {}
}
Block_2D& Container_2D::ref_controlled_block()
{
	for(auto it = BlockData.rbegin(); it != BlockData.rend(); ++it) 
	{
		if(it->isControlled() )
			return *it;
	}
	return BlockData.back(); // if block was not found, selecting last block to control
}
void Container_2D::remove_from_field(points_collection block_parts)
{
	for(auto& field_point : block_parts) { 
		field_grid.put(field_point, field_grid.empty_value());
	}
}
bool Container_2D::projection_to_field(points_collection block_parts) 
{
	for(auto& field_point : block_parts) // check if all points are vacant
	{ 
		if(field_grid.at(field_point) == field_grid.empty_value() ) {
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}
void Container_2D::apply_to_field(points_collection block_new_pos, Block_2D& block)
{
	for(auto& point: block_new_pos ) {
		field_grid.at(point) = block.read_value(point);
	}
}
int Container_2D::height() const
{
	return field_grid.height();
}
int Container_2D::width() const
{
	return field_grid.width();
}
void Container_2D::pushEvent(const Event& event)
{
	events.push(event);
}
void Container_2D::popEvent()
{
	events.pop();
}
bool Container_2D::hasEvents()
{
	return events.empty() ? false : true;
}
Container_2D::Event::ContainerEvent Container_2D::getEvent()
{	
	return events.front().name;
}
std::string Container_2D::row_to_str(const int row_number) const
{
	std::string row_str {""};
	for(auto& elem_pair : field_grid.row(row_number) ) {
		row_str += elem_pair.first;
	}
	return row_str;
}
block_iterator Container_2D::find_block_with_id(const std::size_t search_id)
{
	for(auto it{BlockData.begin()}; it != BlockData.end() ; ++it) {
		if(it->id() == search_id)
			return it;
	}
	return BlockData.end();
}
std::size_t Container_2D::blocks_count() const
{
	return BlockData.size();
}
bool Container_2D::isBurnable_row(std::size_t row_index)
{
	for(auto row_element : field_grid.row(row_index) )
	{
		if(row_element == field_grid.empty_value() ) { // if empty cell found, then this row cannot be deleted
			return false;
		}
		
		if(auto block_iter = find_block_with_id(row_element.second); 
			block_iter != BlockData.end() ) 
		{
			if(not block_iter->isLanded()) { // if block falling, cannot delete either
				return false;
			}
		}
	}
	return true;
}
block_id_set Container_2D::erase_full_lines()
{
	std::vector<std::size_t> filled_rows;
	int height {field_grid.height(int{})};
	for(int i{0}; i < height; ++i) { // create list of rows which should be removed
		if(isBurnable_row(i) )
			filled_rows.emplace_back(i);
	}
	std::set<std::size_t> affected_blocks;
	if(filled_rows.size() == 0) 
		return affected_blocks; // nothing to erase, exit
	
	std::multimap<std::size_t, Point_2D> removal_task; // multimap of "block id" and "value points"

	for(auto it {filled_rows.begin()}; it != filled_rows.end(); ++it) {
		int x_coord {0};
		for(auto row_element : field_grid.row(*it) ) // row_element - is a pair of char and block_id
		{
			removal_task.emplace(row_element.second, Point_2D(*it, x_coord) );
			affected_blocks.emplace(row_element.second);
			++x_coord;
		}
	}
	remove_block_cells(removal_task); // apply changes to container and blocks
	return affected_blocks;
}
void Container_2D::remove_block_cells(std::multimap<std::size_t, Point_2D> removal_task ) 
{	
	std::size_t prev_block_id {0};
	auto block_iter {BlockData.end() };
	
	for(auto& [block_id, point] : removal_task)
	{
		if(block_id != prev_block_id) { 
			block_iter = find_block_with_id(block_id); 
		}
		block_iter->clear_cell(point);  // point is a field coordinate
		field_grid.at(point) = field_grid.empty_value();
		prev_block_id = block_id;
	}
}
void Container_2D::split_blocks(block_id_set block_id )
{
	for(auto& id : block_id) // iterating through blocks which have changed structure
	{
		auto block_iter {find_block_with_id(id) };
		auto grids {block_iter->separate_grids() }; // getting grids after separation
		if(	grids.size() > 1)
		{
			auto grid_iter {grids.begin() };
			auto grid_iter_last {grids.end() };
			block_iter->apply(*grid_iter); // first grid stays in original block instance
			block_iter->mFree();
			++grid_iter;
			while(grid_iter != grid_iter_last ) // other grids move to newly allocated blocks
			{
				auto& block = BlockData.emplace_back(block_iter->frame_coordinates(), *grid_iter);
				block.set_color(Color::Yellow);
				block.mFree();
				apply_to_field(block.field_coordinates(*grid_iter), block );
				++grid_iter;
			}
		}
	}
}
