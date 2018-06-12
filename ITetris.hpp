#ifndef ITETRIS_HPP
#define ITETRIS_HPP

#include "tetris_enums.hpp"

namespace tetris_pdcurses {

class ITetris {
public:
	virtual ~ITetris() = default;
	virtual bool spawnBlock() = 0;
	virtual bool moveBlock(const Direction) = 0;
	virtual bool rotateBlock(const Rotation) = 0;
};

} //namespace tetris_pdcurses

#endif // ITETRIS_HPP