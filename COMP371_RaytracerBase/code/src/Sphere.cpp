//
//  Sphere.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <Eigen/Core>
#include <iostream>
#include "Sphere.h"
#include "Ray.h"

Sphere::Sphere(std::string type, double r, Eigen::Vector3f c, float ka, float kd, float ks, Eigen::Vector3f ac,
               Eigen::Vector3f dc, Eigen::Vector3f sc, float pc)
               : Shape(type, ka, kd,  ks, ac, dc, sc, pc), radius(r), centre(c){
    rSquared = radius * radius;
}
bool Sphere::intersected(Ray *ray){
    float a = ray->getDSquared();
    float b = 2 * ray->getDirection().dot(ray->getOrigin() - centre);
    float c = (ray->getOrigin() - centre).dot(ray->getOrigin() - centre) - rSquared;
    float pos = quadFormula(a, b, c);
    if (pos >= 0){
        Eigen::Vector3f p = ray->atPos(pos);
        Eigen::Vector3f norm = (p - centre).normalized();
        ray->setClosestShape(pos, this, p, norm);
        return true;
    }
    return false;
}
float Sphere::quadFormula(float a, float b, float c){
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
        float x1 = (-b + sqrt(discr)) / (2*a);
        float x2 = (-b - sqrt(discr)) / (2*a);
        if (x1 < x2) {
            return x1;
        }
        return x2;
    }
}
