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

#ifndef D_HPP
#define D_HPP


#include <vector>

class vertex {
public:
    float r, g, b, a;
    float x, y, z;
    vertex();
    void setColor(float r, float g, float b, float a);
    void setPosition(float x, float y, float z);
    void render();
};

class face {
public:
    face();
    float rotx, roty, rotz;
    float scalex, scaley, scalez;
    int setRotation(float, float, float);
    int setScale(float,float,float);
    int addVertex(vertex);
    int render();
private:
    std::vector<vertex> vertexes;
};

//include "3d.cpp" // funtzt so, auskommentiert nicht
#endif /* WING_HPP */