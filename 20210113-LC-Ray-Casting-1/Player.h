/*
 * Player.h
 *
 *  Created on: 28 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <cmath>
#include <memory>
#include <numbers>
#include "Map.h"

class Player
{
protected:
	std::shared_ptr<Map> _map;
	double _x { 0. };
	double _y { 0. };
	double _alpha { 0. };
public:
	Player() = default;

	double x() const { return _x; }
	double y() const { return _y; }
	double alpha() const { return _alpha; }

	void spawn(std::shared_ptr<Map>& map)
	{
		_map = map;
		_x = map->start_x();
		_y = map->start_y();
		_alpha = map->start_a();
	}

	void turn_right(double angle = 0.025)
	{
		_alpha += angle;
		if (_alpha >= std::numbers::pi * 2.)
			_alpha -= std::numbers::pi * 2.;
	}

	void turn_left(double angle = 0.025)
	{
		_alpha -= angle;
		if (_alpha < 0.)
			_alpha += std::numbers::pi * 2.;
	}

	void walk_forward(double dist = 0.05)
	{
		double nx, ny;
		nx = _x + dist * cos(_alpha);
		ny = _y + dist * sin(_alpha);
		if (not _map->is_wall(nx, ny)) {
			_x = nx;
			_y = ny;
		}
	}

	void walk_backward(double dist = 0.05)
	{
		double nx, ny;
		nx = _x - dist * cos(_alpha);
		ny = _y - dist * sin(_alpha);
		if (not _map->is_wall(nx, ny)) {
			_x = nx;
			_y = ny;
		}
	}

	void shift_right(double dist = 0.05)
	{
		double nx, ny;
		nx = _x + dist * cos(_alpha + std::numbers::pi / 2.);
		ny = _y + dist * sin(_alpha + std::numbers::pi / 2.);
		if (not _map->is_wall(nx, ny)) {
			_x = nx;
			_y = ny;
		}
	}

	void shift_left(double dist = 0.05)
	{
		double nx, ny;
		nx = _x + dist * cos(_alpha - std::numbers::pi / 2.);
		ny = _y + dist * sin(_alpha - std::numbers::pi / 2.);
		if (not _map->is_wall(nx, ny)) {
			_x = nx;
			_y = ny;
		}
	}

};



#endif /* PLAYER_H_ */
