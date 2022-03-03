//
//  Ray.cpp
//  
//
//  Created by Ayah Shamma.
//

#include "Ray.h"

Ray::Ray(Eigen::Vector3f p, Eigen::Vector3f d) {
    this->origin = p;
    this->dir = d;
}
Eigen::Vector3f Ray::atPos(double t) {
    Eigen::Vector3f p = this->origin + t * this->dir;
    return p;
}
