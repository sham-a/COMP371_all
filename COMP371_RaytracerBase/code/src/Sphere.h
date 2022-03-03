//
//  Sphere.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Sphere_h
#define Sphere_h

#include <Eigen/Core>
#include "Shape.h"

class Sphere : public Shape {
    double radius;
    Eigen::Vector3f centre;
public:
    Sphere(std::string type, double r, Eigen::Vector3f c);
    virtual bool intersected(Ray ray);
    float quadFormula(float &a, float &b, float &c);
};

#endif /* Sphere_h */
