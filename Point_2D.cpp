#include "Point_2D.hpp"

using namespace tetris_pdcurses;

Point_2D::Point_2D(int y, int x) :Y(y), X(x)
{ }

bool Point_2D::operator==(const Point_2D& rhs) const
{
	return (X == rhs.X) && (Y == rhs.Y);
}
bool Point_2D::operator<(const Point_2D& rhs) const
{
	return (Y < rhs.Y) || ((Y == rhs.Y) && (X < rhs.X)); // return (X < rhs.X) || ((X == rhs.X) && (Y < rhs.Y));
}
void Point_2D::set(const int cY, const int cX) {
	Y = cY;
	X = cX;
}
Point_2D Point_2D::shift(Direction const dir, std::size_t const offset) const
{
	Point_2D target(Y, X);
	switch(dir) {
		case Direction::Up:
			target.Y -= offset;
			break;
		case Direction::Down:
			target.Y += offset;
			break;
		case Direction::Left:
			target.X -= offset;
			break;
		case Direction::Right:
			target.X += offset;
			break;
		case Direction::None:
		default:
			break;
	}
	return target;
}