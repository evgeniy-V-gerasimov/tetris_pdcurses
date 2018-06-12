#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <vector>
#include <cstddef>

namespace tetris_pdcurses {

//class Block;
class Container {
public:
	virtual ~Container() = default;
	Container& operator=(const Container&) = default;
	std::size_t id() const;
protected:
	Container();
private:
	static std::size_t counter;
	std::size_t unit_id;

};

} //namespace tetris_pdcurses
#endif // CONTAINER_HPP