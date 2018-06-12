#ifndef GRID_2D_HPP
#define GRID_2D_HPP

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

#include "tetris_enums.hpp"
#include "Point_2D.hpp"

namespace tetris_pdcurses {

template <typename T = std::string>
class Grid_2D {
public:
	using grid_t = T;
	using value_type = typename T::value_type;
	value_type error_marker;
	value_type null_marker;
	
	Grid_2D(std::size_t length)
		: error_marker('-')
		, null_marker('0') 
		, partition_length(length)
		, matrix(length * length, null_marker) 
	{ } 
	Grid_2D(std::size_t height, std::size_t width)
		: error_marker('-')
		, null_marker('0') 
		, partition_length(width)
		, matrix(width * height, null_marker) 
	{ } 
	Grid_2D(std::pair<std::size_t, grid_t> init_pair)
		: error_marker('-')
		, null_marker('0') 
		, partition_length(init_pair.first)
		, matrix(init_pair.second) 
	{ } 

	bool isValid(const int cY, const int cX) const 
	{
		return (cX >= 0 && cX < width(int{}) ) && (cY >= 0 && cY < height(int{}) );
	}
	bool isValid(const Point_2D pt) const 
	{
		return isValid(pt.Y, pt.X);
	}
	value_type empty_value() const
	{
		return null_marker;
	}
	value_type& at(int const y, int const x)
	{
		if(not isValid(y, x)) 
			return error_marker;
		auto it {matrix.begin()}; 
		std::advance(it, (y * partition_length ) + x );
		return {*it};
	}
	value_type const& at(int const y, int const x) const
	{
		if(not isValid(y, x)) 
			return error_marker;
		auto it {matrix.cbegin()}; 
		std::advance(it, (y * partition_length ) + x );
		return {*it};
	}	
	value_type& at(const Point_2D point)
	{
		return at(point.Y, point.X);
	}
	value_type const& at(const Point_2D point) const
	{
		return at(point.Y, point.X);
	}
	void put(const int y, const int x, const value_type var)
	{
		at(y,x) = var;
	}
	void put(const Point_2D point, const value_type var)
	{
		at(point) = var;
	}
	void put(const std::pair<Point_2D, value_type> input)
	{
		auto const& [point, var] = input;
		at(point) = var;
	}
	std::pair<std::size_t, std::size_t> getDimensions() const 
	{
		return {(matrix.size() / partition_length), partition_length};		
	}
	std::size_t width() const 
	{
		return partition_length;
	}
	std::size_t height() const 
	{
		return {matrix.size() / partition_length};
	}
	int width(int) const
	{
		return {static_cast<int>(partition_length)};
	}
	int height(int) const
	{
		return {static_cast<int>(matrix.size() / partition_length)};
	}
	T column(const std::size_t col_number) const 
	{
		return col(col_number, matrix.cbegin() );
	}
	T rcolumn(const std::size_t col_number) const 
	{
		return col(col_number, matrix.crbegin() );
	}
	T row(const std::size_t row_number) const
	{
		typename T::const_iterator first = matrix.begin() + (row_number * partition_length);
		typename T::const_iterator last = first + partition_length;
		T row_val(first, last);
		return row_val;
	}
	Grid_2D<T> rotate(const Rotation cmd) const
	{
		grid_t rotated_matrix;
		switch(cmd) 
		{
			case Rotation::Tilt_180:
				rotated_matrix = matrix;
				std::reverse(rotated_matrix.begin(), rotated_matrix.end() );
				break;
			case Rotation::Right_p90:
				for(int i {width(int{}) - 1}; i >= 0; --i) 
				{	
					auto revd_col {rcolumn(i)};
					rotated_matrix.insert(rotated_matrix.end(), revd_col.begin(), revd_col.end());
				}
				break;
			case Rotation::Left_n90:
				for(int i {width(int{}) - 1}; i >= 0; --i) 
				{
					auto norm_col {column(i)};
					rotated_matrix.insert(rotated_matrix.end(), norm_col.begin(), norm_col.end());
				}
				break;
			case Rotation::None:
				rotated_matrix = matrix;
				break;
			default:
				break;
		}
		return Grid_2D<T>(partition_length, rotated_matrix);
	}
	std::map<Point_2D, std::size_t> value_points_map() const {
		std::size_t counter {0};
		auto const n_rows {height() };
		std::map<Point_2D, std::size_t> split__map;
		for(std::size_t i{0}; i < n_rows; ++i) {
			Point_2D cursor(0,0);
			cursor.Y += i;
			for(auto it: row(i)) {
				if(it == null_marker) {
					cursor.X += 1;
				}
				else {
					auto ch_top {at( Point_2D(cursor.Y-1, cursor.X) ) };
					auto ch_prev {at( Point_2D(cursor.Y, cursor.X-1) ) };
					if( ch_top == error_marker ) ch_top = null_marker;   // bounds check
					if( ch_prev == error_marker ) ch_prev = null_marker; 
					if( (ch_prev == null_marker) && (ch_top == null_marker) ) 
					{	
						split__map.insert(std::make_pair(Point_2D(cursor.Y, cursor.X),  ++counter ));//auto [iter, status] = 
						cursor.X += 1;
						continue;
					}
					if( (ch_top == null_marker) && (ch_prev != null_marker) ) 
					{
						std::size_t iPrev {0};
						if(auto fnd = split__map.find(Point_2D(cursor.Y, cursor.X-1));
							fnd != split__map.end()) 
						{
							iPrev = fnd->second;
						}
						split__map.insert(std::make_pair(Point_2D(cursor.Y, cursor.X),  iPrev));//auto [iter, status] = 
						cursor.X += 1;
						continue;
					}
					if( (ch_prev == null_marker) && (ch_top != null_marker) )  
					{	
						std::size_t iTop {0};
						if(auto fnd = split__map.find(Point_2D(cursor.Y-1, cursor.X));
							fnd != split__map.end()) 
						{
							iTop = fnd->second;
						}
						split__map.insert(std::make_pair(Point_2D(cursor.Y, cursor.X),  iTop));//auto [iter, status] = 				
						cursor.X += 1;
						continue;
					}
					if( (ch_prev != null_marker) && (ch_top != null_marker) )  
					{
						std::size_t iTop {0};
						std::size_t iPrev {0};
						if(auto fnd = split__map.find(Point_2D(cursor.Y-1, cursor.X));
							fnd != split__map.end()) 
						{
							iTop = fnd->second;						
						}
						if(auto fnd = split__map.find(Point_2D(cursor.Y, cursor.X-1));
							fnd != split__map.end()) 
						{
							iPrev = fnd->second;
						}
						for(auto& element: split__map ){ // fix incorrect id
							if(element.second == iPrev) element.second = iTop;
						}
						split__map[Point_2D(cursor.Y, cursor.X)] = iTop; //split__map.insert(std::make_pair(Point_2D(cursor.Y, cursor.X),  iTop));
						cursor.X += 1;
					}
				}
			}
		}
		return split__map;
	}
	void reset_data(value_type const element) {
		
		auto const n_rows {height() };
		auto const n_cols {width() };
		for(std::size_t y{0}; y < n_rows; ++y) {
			for(std::size_t x{0}; x < n_cols; ++x) {
				auto& ch = at(y,x);
				if(ch == empty_value()){
					continue;
				}
				else {
					ch = element;
				}
			}
		}
	}
	void ios_print() {
		auto const n_rows {height() };
		for(std::size_t i{0}; i < n_rows; ++i ) {
			for(auto& val: row(i)) {
				std::cout << '[' << val << ']';
			}
			std::cout << '\n';
		}
	}
	//friend std::ostream& operator<< <>(std::ostream& os, const Grid_2D<T>& grid_ref);
private:
	std::size_t partition_length; 
	grid_t matrix;
	
	Grid_2D(std::size_t length, grid_t pattern) 
		: error_marker('-')
		, null_marker('0') 
		, partition_length(length)
		, matrix(pattern) 
	{ }

	template<typename c_iterator>
	T col(std::size_t column_number, c_iterator it) const
	{
		T s_column;
		std::advance(it, column_number); 
		s_column.push_back(*it);
		for(int i=1; i < height(int{}); ++i) {
			std::advance(it, partition_length);
			s_column.push_back(*it);
		}
		return s_column;
	}
};

std::ostream& operator<< (std::ostream& os, Grid_2D<std::string>& grid_ref);
std::ostream& operator<< (std::ostream& os, Grid_2D<std::vector<int>>& grid_ref);
std::ostream& operator<< (std::ostream& os, Grid_2D<std::vector<std::pair<char, int>>>& grid_ref);

/*
template<>
Grid_2D<std::string>::Grid_2D(std::size_t length);
template<>
Grid_2D<std::string>::Grid_2D(std::size_t height, std::size_t width);
template<>
Grid_2D<std::string>::Grid_2D(std::pair<std::size_t, grid_t> init_pair);
*/

template<>
Grid_2D<std::vector<std::pair<char, int>> >::Grid_2D(std::size_t length);
template<>
Grid_2D<std::vector<std::pair<char, int>> >::Grid_2D(std::size_t height, std::size_t width);

template<>
Grid_2D<std::vector<int>>::Grid_2D(std::size_t length);
template<>
Grid_2D<std::vector<int>>::Grid_2D(std::size_t height, std::size_t width);



}

#endif // GRID_2D_HPP