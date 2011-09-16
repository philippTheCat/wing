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

//system includes
#include <iostream>
#include <sstream>
//#include <windows.h>

using namespace std;
using std::string;

//3d includes
#include "SDL/SDL_opengl.h" 
#include <GL/glu.h>



//engine
#include "wing.hpp"
#include "3d.hpp"
#include "timer.hpp"
#include "importers.hpp"




const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//The attributes of the square
const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;

//Event handler
SDL_Event event;


class wi : public wing {
	public:
            object obj;
	 int setUp();
	 int render();
         int update();
         int run();
            //Timer used to calculate the frames per second
        Timer fps;
            
        //Timer used to update the caption
        Timer updateFPS;
        double rotation;
};
int wi::run(){
    while (update()){
        render();
    }
}

int wi::update() {
    while (SDL_PollEvent(&event)) {
        //Handle key presses

        if (event.type == SDL_QUIT) {
            return false;
        }
    }


    return true;
}

int wi::setUp(){
    obj = importObj("data/cube.obj");
    rotation = 0;
    
    return true;
}

int wi::render(){

 fps.start();
 glClear(GL_COLOR_BUFFER_BIT);
 glClear(GL_DEPTH_BUFFER_BIT);

 glLoadIdentity();

 gluLookAt(
         5,5,-5,
         0,0,0,
         0,1,0); 
  

  //light
  float position[]  =   {5,   5,    -5};
  float ambient[]   =   {0.8, 0.8,  0.8, 1.0};
  float diffuse[]   =   {0.8, 0.8,  0.8, 1.0};

//    glLightfv(GL_LIGHT0, GL_AMBIENT,  ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE,  diffuse);
//    glLightfv(GL_LIGHT0, GL_POSITION, position);
//    glEnable(GL_LIGHT0);
 glBegin(GL_TRIANGLES);
  
  vertex v1;
    v1.setPosition(-1,-1,0);
    v1.setColor(1.0,0,0,1);

        vertex v3;
    v3.setPosition(1,-1,0);
        v3.setColor(0,1,0,1);

    
    vertex v4;
    v4.setPosition(0,1,0);
        v4.setColor(0,0,1,1);

        face f;
        f.addVertex(v1);
        f.addVertex(v3);
        f.addVertex(v4);
        //f.render();
    glEnd();

 obj.render();
  SDL_GL_SwapBuffers();
  
  fps.tick();
}


int main(int argc, char *argv[]) {
	cout << "running" << endl;
	bool testing = false;
	for( int i = 0; i < argc; i++ )
	{
		if (string(argv[i]).compare("--test")==0){
			testing = true;
			cout << "running tests\n";
		}
	}

        wi w;
        
#ifdef win32
        //fixing cout and cerr
        freopen( "CON", "w", stdout );
        freopen( "CON", "w", stderr );
#endif
	w.setUp();
	w.run();
        
//	if (testing){
//		wi w;
//		w.setUp();
//		w.run();
//	} else {
//		wing w;
//		w.setUp();
//		w.run();
//	}
	return EXIT_SUCCESS;
}

