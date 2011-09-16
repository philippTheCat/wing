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

#include "importers.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;


template <class T>
bool from_string(T& t, 
                 const std::string& s, 
                 std::ios_base& (*f)(std::ios_base&))
{
  std::istringstream iss(s);
  return !(iss >> f >> t).fail();
}

object importObj(string file){
    std::vector<vertex> vertexes;
    std::vector<face> faces;

    object obj;
    
    fstream objfile;
    
    string word;

 
    objfile.open(file.c_str(),ios::in);

    if (objfile.is_open()) {
        string line;
        while (objfile.good()) {
            
            getline(objfile, line);
            istringstream iss(line, istringstream::in);

            try {
                string type;
                while (iss >> type) {
                    break;
                }
                if (type.compare("#") == 0){
                    continue;
                } else if (type.compare("v") == 0){
                    cout << "new vertex:" << endl;
                    float nr;
                    
                    std::vector<float> nrs;

                    
                    while (iss >> nr) {
                        nrs.push_back(nr );
                    }
                    
                    if (nrs.size() == 3){
                        vertex v;
                        v.setPosition((float)nrs[0],(float)nrs[1],(float)nrs[2]);
                        v.setColor(1,1,1,1);
                        vertexes.push_back(v);
                        cout << v.toString() << endl; 
                    }
                    continue;
                } else if (type.compare("f") == 0){
                    cout << "new face:" << endl;
                    string nr;
                  
                    std::vector<vertex> vrtxes;

              
                    while (iss >> nr) {
                        cout << vertexes.size() << endl;
                         istringstream nriss(nr, istringstream::in);
                         int n;
                         char c;
                         bool even = false;
                         while (nriss >> n) {

                                cout << "vertex " << n << endl;
                                nriss >> c;
                                nriss >> c;
                                nriss >> c;
                                vrtxes.push_back(vertexes[n-1]);



                        }

                    }
                    if (vrtxes.size() == 3){
                        face v;
                        v.addVertex(vrtxes[0]);
                        v.addVertex(vrtxes[1]);
                        v.addVertex(vrtxes[2]);
                        obj.addFace(v);
                        //cout << v.toString() << endl; 
                    } else {
                        cout << "error, face which is not a tri" << endl;
                    }
                    continue;
                }
                
            } catch (char * str) {
                cout << "error loading OBJ: " << str << endl;
            }

        }
    } else {
        cout << "error: could not load OBJ from file: " << file << endl;
    }
    
    objfile.close();
    
    cout << __LINE__ << endl;   
    return obj;
}
