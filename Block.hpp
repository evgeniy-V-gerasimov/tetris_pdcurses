#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstddef>
#include "tetris_enums.hpp"

namespace tetris_pdcurses {

class Block {
public:
	virtual ~Block();
	Block& operator=(const Block&) = default;
	std::size_t id() const;
	bool isLanded() const;
	bool isFalling() const;
	bool isControlled() const;
	bool isRemoved() const;
	void mFree() const;
	void mLanded() const;
	void mRemoved() const;
protected:
	Block(Shape);
	Shape unit_shape;
private:
	enum class ControlState : std::uint8_t {
		Landed,
		Falling,
		Controlled,
		Removed
	};
	static std::size_t counter;
	std::size_t unit_id;
	mutable ControlState flag;
};

} //namespace tetris_pdcurses
#endif // BLOCK_HPP