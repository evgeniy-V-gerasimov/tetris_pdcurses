#ifndef POINT_2D_HPP
#define POINT_2D_HPP

#include <cstddef>

#include "tetris_enums.hpp"

namespace tetris_pdcurses {

class Point_2D final{
public:
	int Y; 
	int X;
	
	explicit Point_2D(int, int);
	bool operator==(const Point_2D&) const;
	bool operator<(const Point_2D&) const;
	void set(const int, const int);
	Point_2D shift(const Direction, const std::size_t) const;
};

} //namespace tetris_pdcurses
#endif // POINT_2D_HPP