#ifndef TETRIS_ENUMS_HPP
#define TETRIS_ENUMS_HPP

#include <cstdint>

namespace tetris_pdcurses 
{

	enum class Shape : std::uint8_t {
		Line = 1,
		L,
		rL,	//reversed L
		N,
		rN, //reversed N
		T,
		Box,
		Dot,
		extBlock1,
		extBlock2,
		extBlock3,
		extBlock4,
		extBlock5,
		extBlock6,
		extBlock7,
		extBlock8,
		Custom,
		Test = 42
	};
	
	enum class Direction : std::uint8_t {
		None = 0,
		Up,
		Down,
		Left,
		Right
	};
	
	enum class Rotation : std::uint8_t {
		None = 0,
		Tilt_180,
		Right_p90,
		Left_n90
	};
	
	enum class Color : std::uint8_t  {
		Black = 0,
		Red,
		Green,
		Blue,
		Cyan,
		Magenta,
		Yellow,
		White,
		Ghost
	};
}

#endif // TETRIS_ENUMS_HPP