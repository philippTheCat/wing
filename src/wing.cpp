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

//#include "wing.hpp" //funtzt so, einkommentiert nicht

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h" 

#include <iostream>
using namespace std;

#include "wing.hpp"

/*
 * Here Be Dragons
 */

int wing::eventhandler(SDL_Event event){
    if( event.type == SDL_QUIT ) {
			return false;
		}
            if( event.type == SDL_VIDEORESIZE )
    {
        //Resize the screen
        screen = SDL_SetVideoMode( event.resize.w, event.resize.h, 32, SDL_OPENGL | SDL_RESIZABLE );
       //Set clear color
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity;
        gluPerspective(60, event.resize.w/event.resize.h, 0.1, 100);
        glMatrixMode(GL_MODELVIEW);
        glViewport(0, 0, event.resize.w, event.resize.h);
    }
}

void wing::SignalHandler(int s){
			running = false;
           //quit();
           //exit(1); 

}

bool wing::running = true;


wing::wing(){

    frame = 0;

   	SDL_Init( SDL_INIT_EVERYTHING );

    screen = SDL_SetVideoMode( 800, 600, 32, SDL_OPENGL | SDL_RESIZABLE);

    if (initGL() == false) { 
	    quit("could not initialize OpenGL");
	} 

}

int wing::initGL(){
	   //Set clear color
       int width = 800;
       int height = 600;


    glViewport( 0, 0, ( GLint )width, ( GLint )height );


    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity( );


    /* Set our perspective */
    gluPerspective( 45.0f, 800/600, 0.1f, 100.0f );


    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );



 
 glClear(GL_COLOR_BUFFER_BIT);
 glClear(GL_DEPTH_BUFFER_BIT);
 
 glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);


    //If there was any errors
    GLenum errCode;
    const GLubyte *errString;
    errCode = glGetError();
    if ( errCode != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
       cout << "OpenGL error:" << errString << endl;
      return false;
    }

    //If everything initialized
    return true;
}

int wing::setUp(){
	    hello = SDL_LoadBMP( "hello.bmp" );

	return true;
}


int wing::update(){
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) { 
            if (!eventhandler(event)==1){
                return false;
            }
	}
	return true;
}


int wing::render(){

	 SDL_BlitSurface( hello, NULL, screen, NULL );

    //Update Screen
    SDL_Flip( screen );

    //Pause
    SDL_Delay( 50 );
	return true;
}


int wing::run(){
	while (update()==true && running){
		render();
	}
	//cout << "stopping\n";
	cout << "running = "<< running << "\n";
	quit();
}

int wing::quit(string message){
	cout << "error: " << message <<endl;
	quit();
}
int wing::quit(){
	SDL_FreeSurface( hello );

	cout << "wing::quit\n";
	SDL_Quit();
	return true;
}


