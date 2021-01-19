/*
 * Window.cc
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: unyuu
 */

#include "Window.h"
#include <stdexcept>
#include <string>

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
					SDL_RENDERER_ACCELERATED),
			SDL_DestroyRenderer);
	if (_renderer == nullptr)
		throw std::runtime_error(
				"Failed to create a renderer: "s +
				SDL_GetError());
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

}

void Window::handle_event(const SDL_Event & event)
{

}

void Window::handle_keys(const Uint8 * keys)
{

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

	for (int col = 0; col < width(); col++) {
		draw_col(col, 400);
	}
}

void Window::draw_col(int col, int h)
{
	SDL_SetRenderDrawColor(_renderer.get(), 32, 128, 48, 255);
	SDL_RenderDrawLine(_renderer.get(),
			col, height()/2 - h/2,
			col, height()/2 + h/2);
}

