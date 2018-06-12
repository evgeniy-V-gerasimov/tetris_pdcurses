#include <stdexcept>
#include <memory>

#include "IGame.hpp"
#include "TetrisClassicPDC.hpp"

int main(int argc, char** argv)
{
	using namespace tetris_pdcurses;
	{
	std::unique_ptr<IGame> tetris (new TetrisClassicPDC());
	tetris->exec();
	}
	return 0;
}

//#include <vector>
//#include <string>
//#include <string_view>
//#include <chrono>
//#include <set>
//#include <functional>
//#include <tuple>
//#include "curses.h"
//#include <boost/random/random_device.hpp>
//#include <boost/random/uniform_int_distribution.hpp>
//#include "tetris_enums.hpp"
//#include "Point_2D.hpp"
//#include "Tetris.hpp"
//#include "IGame.hpp"
//#include "Block.hpp"
//#include "Block_2D.hpp"
//#include "Container.hpp"
//#include "Container_2D.hpp"
//#include "Grid_2D.hpp"
