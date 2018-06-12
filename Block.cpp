#include "Block.hpp"

using namespace tetris_pdcurses;

std::size_t Block::counter {0};

Block::Block(Shape init_shape) 
	: unit_shape(init_shape)
	, unit_id(++counter)
	, flag(ControlState::Controlled)
{

}
Block::~Block(){
	
}
std::size_t Block::id() const
{
	return unit_id;
}
bool Block::isLanded() const
{
	return flag == ControlState::Landed;
}
bool Block::isFalling() const
{
	return flag == ControlState::Falling;
}
bool Block::isControlled() const
{
	return flag == ControlState::Controlled;
}
bool Block::isRemoved() const
{
	return flag == ControlState::Removed;
}
void Block::mFree() const
{
	flag = ControlState::Falling;
}
void Block::mLanded() const
{
	flag = ControlState::Landed;
}
void Block::mRemoved() const
{
	flag = ControlState::Removed;
}
