/*
 * Window.h
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: unyuu
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <memory>
#include <SDL2/SDL.h>

class Window
{
public:
	static constexpr int DEFAULT_WIDTH = 1920;
	static constexpr int DEFAULT_HEIGHT = 1080;

protected:
	std::shared_ptr<SDL_Window> _window;
	std::shared_ptr<SDL_Renderer> _renderer;
	int _width, _height;

public:
	Window(	int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT);

	int width() const { return _width; }
	int height() const { return _height; }

	void main_loop();

	void setup();
	void handle_event(const SDL_Event & event);
	void handle_keys(const Uint8 * keys);
	void logic();
	void render();

	void draw_col(int col, int h);
};



#endif /* WINDOW_H_ */
