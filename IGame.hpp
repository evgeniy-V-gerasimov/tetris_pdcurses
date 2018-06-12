#ifndef IGAME_HPP
#define IGAME_HPP

namespace tetris_pdcurses {

class IGame {
public:
	virtual int  exec() = 0;
	virtual int  random() = 0;
	virtual void processInput() = 0;
	virtual void rendering() = 0;
	virtual void update() = 0;
	virtual ~IGame() = default;
};

} //namespace tetris_pdcurses
#endif // IGAME_HPP