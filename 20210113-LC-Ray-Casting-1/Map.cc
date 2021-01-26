/*
 * Map.cc
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: unyuu
 */

#include <fstream>
#include <sstream>
#include "Map.h"

Map::Map(const char * filename)
{
	std::ifstream file;
	file.exceptions(std::ifstream::badbit);
	file.open(filename);

	std::string line;

	std::getline(file, line);
	std::stringstream params(line);
	params >> _width >> _height >> _start_x >> _start_y >> _start_a;

	_map.resize(_height);
	for (int i = 0; i < _height; i++) {
		std::getline(file, _map[i]);
	}

	file.close();
}


