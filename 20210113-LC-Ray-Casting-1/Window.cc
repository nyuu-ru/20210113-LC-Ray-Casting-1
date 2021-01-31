/*
 * Window.cc
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: unyuu
 */

#include "Window.h"
#include <stdexcept>
#include <string>
#include <cmath>
#include <numbers>

Window::Window(int width, int height)
: _width(width), _height(height)
{
	using namespace std::literals;

	_window = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
					"Ray Casting",
					SDL_WINDOWPOS_CENTERED_DISPLAY(1),
					SDL_WINDOWPOS_CENTERED_DISPLAY(1),
					_width, _height,
					SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (_window == nullptr)
		throw std::runtime_error(
				"Failed to create a window: "s +
				SDL_GetError());

	_renderer = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(
					_window.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (_renderer == nullptr)
		throw std::runtime_error(
				"Failed to create a renderer: "s +
				SDL_GetError());

	SDL_SetRenderDrawBlendMode(_renderer.get(), SDL_BLENDMODE_BLEND);

	_map = std::make_shared<Map>("map1.txt");
	_player = std::make_shared<Player>();
}

void Window::main_loop()
{
	setup();

	SDL_Event event;
	auto keys = SDL_GetKeyboardState(nullptr);
	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				return;
			handle_event(event);
		}
		handle_keys(keys);

		logic();

		render();
		SDL_RenderPresent(_renderer.get());
	}
}

void Window::setup()
{
	_player->spawn(_map);

}

void Window::handle_event(const SDL_Event & event)
{

}

void Window::handle_keys(const Uint8 * keys)
{
	if (keys[SDL_SCANCODE_E]) _player->turn_right();
	if (keys[SDL_SCANCODE_Q]) _player->turn_left();
	if (keys[SDL_SCANCODE_W]) _player->walk_forward();
	if (keys[SDL_SCANCODE_S]) _player->walk_backward();
	if (keys[SDL_SCANCODE_D]) _player->shift_right();
	if (keys[SDL_SCANCODE_A]) _player->shift_left();
}

void Window::logic()
{

}

void Window::render()
{
	SDL_Rect r_sky { 0, 0, width(), height() / 2 };
	SDL_Rect r_floor { 0, height() / 2, width(), height() / 2 };
	SDL_SetRenderDrawColor(_renderer.get(),
			96, 128, 192, 255);
	SDL_RenderFillRect(_renderer.get(), &r_sky);
	SDL_SetRenderDrawColor(_renderer.get(),
			64, 64, 64, 255);
	SDL_RenderFillRect(_renderer.get(), &r_floor);

	using namespace std::numbers;

	double x = _player->x();
	double y = _player->y();
	double alpha = _player->alpha();
	double fov = pi / 3.;
	double d = double(width()) / 2. / tan(fov / 2.);
	double H = CELL_HEIGHT;
	int h;

	for (int col = 0; col < width(); col++) {
		double gamma = (double(col) / double(width()) - 0.5) * fov;
		double beta = alpha + gamma;
		double Dh, Dv, D;
		double rx, ry, dx, dy;

		static constexpr double EPS = 0.001;

		if (cos(beta) > EPS) {
			rx = floor(x) + EPS;
			dx = 1.;
			dy = tan(beta);
			ry = y - (x - rx) * dy;
			cast_ray(rx, ry, dx, dy);
			Dv = hypot(rx-x, ry-y);
		} else if (cos(beta) < -EPS) {
			rx = ceil(x) - EPS;
			dx = -1.;
			dy = tan(-beta);
			ry = y - (rx - x) * dy;
			cast_ray(rx, ry, dx, dy);
			Dv = hypot(rx-x, ry-y);
		} else {
			Dv = INFINITY;
		}

		if (sin(beta) > EPS) {
			ry = floor(y) + EPS;
			dy = 1.;
			dx = 1./tan(beta);
			rx = x - (y - ry) * dx;
			cast_ray(rx, ry, dx, dy);
			Dh = hypot(rx-x, ry-y);
		} else if (sin(beta) < -EPS) {
			ry = ceil(y) - EPS;
			dy = -1.;
			dx = 1./tan(-beta);
			rx = x - (ry - y) * dx;
			cast_ray(rx, ry, dx, dy);
			Dh = hypot(rx-x, ry-y);
		} else {
			Dh = INFINITY;
		}

		if (Dv < Dh) {
			D = Dv;
		} else {
			D = Dh;
		}

		h = int(H * d / (D * cos(gamma)));

		draw_col(col, h);
	}

	for (int x = 0; x < _map->width(); ++x)
		for (int y = 0; y < _map->height(); ++y) {
			SDL_Rect r_cell {
				x * MAP_CELL_SIZE,
				y * MAP_CELL_SIZE,
				MAP_CELL_SIZE,
				MAP_CELL_SIZE };
			if (_map->is_wall(x, y))
				SDL_SetRenderDrawColor(_renderer.get(),
						255, 255, 255, 127);
			else
				SDL_SetRenderDrawColor(_renderer.get(),
						0, 0, 0, 63);
			SDL_RenderFillRect(_renderer.get(), &r_cell);
		}
}

void Window::cast_ray(double & rx, double & ry, double dx, double dy)
{
	do {
		rx += dx;
		ry += dy;
	} while (not _map->is_wall(rx, ry));
}

void Window::draw_col(int col, int h)
{
	SDL_SetRenderDrawColor(_renderer.get(), 32, 128, 48, 255);
	SDL_RenderDrawLine(_renderer.get(),
			col, height()/2 - h/2,
			col, height()/2 + h/2);
}

