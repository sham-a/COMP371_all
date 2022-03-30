//
//  Ray.cpp
//  
//
//  Created by Ayah Shamma.
//

#include "Ray.h"

Ray::Ray(Eigen::Vector3f p, Eigen::Vector3f d) {
    origin = p;
    dir = d;

    dSquared = dir.dot(dir);
    intersectedShape = nullptr;
}
Eigen::Vector3f Ray::atPos(double t) {
    Eigen::Vector3f p = this->origin + t * this->dir;
    return p;
}
void Ray::setClosestShape(float possibleT, Shape *shapeHit, Eigen::Vector3f pointHit, Eigen::Vector3f normalHit) {
    if (intersectedShape != nullptr) {
        if (t < possibleT) {
            return;
        }
    }
    this->t = possibleT;
    this->point = pointHit;
    this->normal = normalHit;
    this->intersectedShape = shapeHit;
}