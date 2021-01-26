/*
 * Map.h
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

class Map
{
protected:
	int _width {0}, _height {0};
	double _start_x {0.}, _start_y {0.}, _start_a {0.};
	std::vector<std::string> _map;
public:
	Map(const char * filename);

	int width() const { return _width; }
	int height() const { return _height; }

	double start_x() const { return _start_x; }
	double start_y() const { return _start_y; }
	double start_a() const { return _start_a; }

	bool is_wall(int x, int y) const
	{
		if (x < 0 or y < 0 or x >= _width or y >= _height)
			return true;
		return _map[y][x] == '#';
	}
};



#endif /* MAP_H_ */
