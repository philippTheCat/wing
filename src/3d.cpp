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

#include "SDL/SDL_opengl.h" 
#include <GL/glu.h>
#include <vector>
#include "3d.hpp"

#include <iostream>
using namespace std;

string convertDouble(double value) {
  std::ostringstream o;
  if (!(o << value))
    return "";
  return o.str();
}

Vector3d::Vector3d(float _x,float _y ,float _z){
    this->x = _x;
    this->y = _y;
    this->z = _z;
}
Vector3d::Vector3d(float s){
    Vector3d(s,s,s);
}
Vector3d::Vector3d(){
    Vector3d(1,1,1);
}




vertex::vertex(){
    this->x,this->y,this->z = 0;
    this->r = 1.0;
    this->g = 1.0;
    this->b = 1.0;
    this->a = 1.0;
}
void vertex::setColor(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
    
void vertex::setPosition(float x, float y,float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

void vertex::render(){
    
    glColor3f(r,g,b);      // Ab jetzt werden alle gezeichneten Punkte rot
    glVertex3f(x,y,z); // Der erste Eckpunkt ist mittig und 100 Pixel
}

string vertex::toString(){
    std::ostringstream out;
    out << "<vertex on x: ";
    out << x;
    out << " y: ";
    out << y;
    out << " z: ";
    out << z;
    out << ">";
    out << endl;
    return out.str();
    //return "<vertex on x: " << convertDouble(x).c_str() << " y: " << y << " z: " << z << " >";
}
face::face(){
    this->setScale(1,1,1);
}

int face::addVertex(vertex v){
    vertexes.push_back(v);
    return 1;
}

int face::render(){
    glPushMatrix();
    glScalef (scalex,scaley,scalez);
    glRotatef(rotx,1,0,0);
    glRotatef(roty,0,1,0);
    glRotatef(rotz,0,0,1);
        switch (vertexes.size()){
            case 1:
                glBegin(GL_POINT);
                break;
            case 2:
                glBegin(GL_LINES);
            case 3:
                glBegin(GL_TRIANGLES);
                break;
            default:
                cout << "I cant process "<< vertexes.size() << "vertexes" << endl;
                return 0;
        }

        int size = vertexes.size();
        for (vector<vertex>::iterator it = vertexes.begin(); it!=vertexes.end(); ++it) {
            ((vertex)*it).render();
        }
        glEnd();
    glPopMatrix();
}

int face::setRotation(float x, float y, float z){
    this->rotx = x;
    this->roty = y;
    this->rotz = z;
    return 1;
}

int face::setScale(float x, float y , float z ){
    this->scalex = x;
    this->scaley = y;
    this->scalez = z;
    return 1;
}

Vector3d face::getNormal(){
    GLfloat Qx, Qy, Qz, Px, Py, Pz;

    if (vertexes.size() < 3){
        Vector3d v;
        return v;
    }
    
    vertex fVert1 = vertexes[0];
    vertex fVert2 = vertexes[1];
    vertex fVert3 = vertexes[2];
    
    
   Qx = fVert2.x-fVert1.x;
   Qy = fVert2.y-fVert1.y;
   Qz = fVert2.z-fVert1.z;
   Px = fVert3.x-fVert1.x;
   Py = fVert3.y-fVert1.y;
   Pz = fVert3.z-fVert1.z;

  float fNormalX = Py*Qz - Pz*Qy;
  float fNormalY = Pz*Qx - Px*Qz;
  float fNormalZ = Px*Qy - Py*Qx;
  
  return Vector3d(fNormalX,fNormalY,fNormalZ);
}

object::object(){
    this->setScale(1,1,1);
}

int object::addFace(face f){
    this->faces.push_back(f);
    return 1;
}

int object::render() {
    glPushMatrix();
        glScalef (scalex,scaley,scalez);
        glRotatef(rotx,1,0,0);
        glRotatef(roty,0,1,0);
        glRotatef(rotz,0,0,1);

        for (vector<face>::iterator it = faces.begin(); it != faces.end(); ++it) {
            ((face) * it).render();
        }
    glPopMatrix();
}

int object::setRotation(float x, float y, float z){
    this->rotx = x;
    this->roty = y;
    this->rotz = z;
    return 1;
}

int object::setScale(float x, float y , float z ){
    this->scalex = x;
    this->scaley = y;
    this->scalez = z;
    return 1;
}