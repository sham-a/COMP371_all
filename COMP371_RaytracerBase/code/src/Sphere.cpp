//
//  Sphere.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <stdio.h>
#include <Eigen/Core>
#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(std::string type, double r, Eigen::Vector3f c) : Shape(type){
    this->radius = r;
    this->centre = c;
}
bool Sphere::intersected(Ray ray){
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2 * ray.getDirection().dot(ray.getOrigin() - this->centre);
    float c = (ray.getOrigin() - this->centre).dot((ray.getOrigin() - this->centre)) - this->radius;
    float pos = quadFormula(a, b, c);
    if (pos < 0){
        return false;
    }
    return true;
}
float Sphere::quadFormula(float &a, float &b, float &c){
    float discr = b * b - 4 * a * c;
    // no real solution
    if (discr < 0) {
        return -std::numeric_limits<float>::infinity();
    }
    // one real solution
    else if (discr == 0) {
        return -b / (2 * a);
    }
    // two real solutions
    else {
        float x1 = (-b + discr) / (2*a);
        float x2 = (-b - discr) / (2*a);
        if (x1 < x2) {
            if (x1 > 0) {
                return x1;
            }
        }
        return x2;
    }
}
