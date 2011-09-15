/* This file is part of Wing.
 * 
 * Wing is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Wing is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Wing.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <signal.h>
#include "SDL/SDL.h"
#include <iostream>


using namespace std;

#ifndef WING_HPP
#define WING_HPP
#include "timer.hpp"


class wing{
private:
    public:
        wing();
        int setUp();
        int update();
        int render();
        int run();
        int initGL();
        int quit();
        int quit(string);
        int eventhandler(SDL_Event event);
        void static SignalHandler(int);
	bool static  running;

	SDL_Surface* hello;
    	SDL_Surface* screen;
        int frame;
    
        //Timer used to calculate the frames per second
        Timer fps;
            
        //Timer used to update the caption
        Timer updateFPS;

};
#endif /* WING_HPP */

