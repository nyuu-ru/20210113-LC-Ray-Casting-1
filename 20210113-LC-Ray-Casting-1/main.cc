/*
 * main.cc
 *
 *  Created on: 13 янв. 2021 г.
 *      Author: unyuu
 */

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>

#include "Window.h"

int main(int, char **)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	try {
		Window w;

		w.main_loop();

	} catch (const std::exception & e) {
		std::cerr << "An exception has occured:\n"
				<< e.what() << std::endl;
	} catch (...) {
		std::cerr << "An unknown error occured!" << std::endl;
		return 1;
	}

	return 0;
}

