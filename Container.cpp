#include "Container.hpp"

using namespace tetris_pdcurses;

std::size_t Container::counter {0};

Container::Container() :unit_id(++counter)
{ }
std::size_t Container::id() const
{
	return unit_id;
}