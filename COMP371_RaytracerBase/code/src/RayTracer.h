//
//  RayTracer.h
//  
//
//  Created by Ayah Shamma on 2022-02-01.
//

#ifndef RayTracer_h
#define RayTracer_h

#include "../external/json.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <string>
#include "Shape.h"

using namespace nlohmann;
using namespace std;

//forward declaration
//class Shape;

class RayTracer {
    Shape *shape;               // main shape of the scene
    nlohmann::json j;
    int dimx;                   // image width
    int dimy;                   // image height
    Eigen::Vector3f o;          // center vector
    Eigen::Vector3f l;          // look-at vector
    Eigen::Vector3f u;          // up vector
    double fov;                 // field of view angle
    Eigen::Vector3f ac;         // ambient color
    Eigen::Vector3f dc;         // diffuse color
    Eigen::Vector3f sc;         // specular color
    
public:
    RayTracer(nlohmann::json j);
    void run();
    void readJSON();
    Eigen::Vector3f createDirVector(int i, int j);
};




#endif /* RayTracer_h */
