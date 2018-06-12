#ifndef TETRISCLASSICPDC_HPP
#define TETRISCLASSICPDC_HPP

#include <vector>
#include <chrono>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <variant>

#include "curses.h" // PDCurses 3.4
#include "IGame.hpp"
#include "ITetris.hpp"
#include "Point_2D.hpp"
#include "Block_2D.hpp"
#include "Container_2D.hpp"
#include "tetris_enums.hpp"

namespace tetris_pdcurses {

class TetrisClassicPDC: public IGame, public ITetris {
public:
	TetrisClassicPDC();
	~TetrisClassicPDC();

    int  exec() override;
	int  random() override;
	void processInput() override;
	void rendering() override;
	void update() override;
	
	bool spawnBlock() override;
	bool moveBlock(const Direction) override;
	bool rotateBlock(const Rotation) override;

	void operator()(const Container_2D::Event::BlockLanded&);
	void operator()(const Container_2D::Event::CtrlBlockLanded&);
	void operator()(const Container_2D::Event::Sanitize&);

	Shape getRandomShape();
private:
	
	Container_2D game_field;
	WINDOW* tetris_window; // pdcurses WINDOW
    int startx; 
	int starty; // starting position for tetris_window, width and height
	int pdc_window_width;
	int pdc_window_height;
    int ch;
	int pdc_input;
	bool exit_game;
	boost::random::random_device rng;
    boost::random::uniform_int_distribution<> index_dist;
    
    std::chrono::steady_clock::time_point 	L_time_point;
    std::chrono::steady_clock::duration 	L_time_span, 
											L_prev_time_span;
	
	void draw_border() const;
	void draw_blocks_counter() const;
	void draw_game_field(const int, const int) const;
	void processEvents();
};

} //namespace tetris_pdcurses
#endif // TETRISCLASSICPDC_HPP