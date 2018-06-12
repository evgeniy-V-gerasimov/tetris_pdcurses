#include "Grid_2D.hpp"

using namespace tetris_pdcurses;
/*
template<>
Grid_2D<std::string>::Grid_2D(std::size_t length)
	: error_marker('-')
	, null_marker('0')
	, partition_length(length)
	, matrix(length * length, null_marker)
{

}
template<>
Grid_2D<std::string>::Grid_2D(std::size_t height, std::size_t width)
	: error_marker('-')
	, null_marker('0')
	, partition_length(width)
	, matrix(width * height, null_marker)
{

}
template<>
Grid_2D<std::string>::Grid_2D(std::pair<std::size_t, grid_t> init_pair)
	: error_marker('-')
	, null_marker('0')
	, partition_length(init_pair.first)
	, matrix(init_pair.second)
{

}
*/
template<>
Grid_2D<std::vector<std::pair<char, int>> >::Grid_2D(std::size_t length)
	: error_marker({'-', -1})
	, null_marker({'0', 0})
	, partition_length(length)
	, matrix(length * length, null_marker)
{

}
template<>
Grid_2D<std::vector<std::pair<char, int>> >::Grid_2D(std::size_t height, std::size_t width)
	: error_marker({'-', -1})
	, null_marker({'0', 0})
	, partition_length(width)
	, matrix(width * height, null_marker)
{

}

template<>
Grid_2D<std::vector<int>>::Grid_2D(std::size_t length) 
	: error_marker(-1)
	, null_marker(0)
	, partition_length(length)
	, matrix(length * length, null_marker)
{

}
template<>
Grid_2D<std::vector<int>>::Grid_2D(std::size_t height, std::size_t width) 
	: error_marker(-1)
	, null_marker(0)
	, partition_length(width)
	, matrix(width * height, null_marker)
{

}

std::ostream& operator<< (std::ostream& os, Grid_2D<std::string>& grid_ref)
{
	for(std::size_t i{0}; i < grid_ref.height(); ++i ) 
	{
		for(auto& val: grid_ref.row(i))
		{
			os << '[' << val << ']';
		}
		os << '\n';
	}
	return os;
}

std::ostream& operator<< (std::ostream& os, Grid_2D<std::vector<int>>& grid_ref)
{
	for(std::size_t i{0}; i < grid_ref.height(); ++i ) 
	{
		for(auto& val: grid_ref.row(i))
		{
			os << '[' << val << ']';
		}
		os << '\n';
	}
	return os;
}
std::ostream& operator<< (std::ostream& os, Grid_2D<std::vector<std::pair<char, int>>>& grid_ref)
{
	for(std::size_t i{0}; i < grid_ref.height(); ++i ) 
	{
		for(auto& val: grid_ref.row(i))
		{
			os << '[' << val.first << '|' << val.second << ']';
		}
		os << '\n';
	}
	return os;
}
