//
//  Ray.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Ray_h
#define Ray_h

#include <Eigen/Core>
#include "Shape.h"

class Ray {
    Eigen::Vector3f origin;         // origin of ray vector
    Eigen::Vector3f dir;            // direction of ray vector

    // Variable frequently used
    float dSquared;                 // ray.dir dot ray.dir

    // Record for the closest object the ray has hit.
    float t;
    Eigen::Vector3f point;
    Eigen::Vector3f normal;
    Shape *intersectedShape;
public:
    Ray(Eigen::Vector3f p, Eigen::Vector3f d);
    Eigen::Vector3f atPos(double t);
    void setClosestShape(float possibleT, Shape *shapeHit, Eigen::Vector3f pointHit, Eigen::Vector3f normalHit);
    Eigen::Vector3f getDirection() { return dir; };
    Eigen::Vector3f getOrigin() { return origin; };
    float getDSquared() const { return dSquared; };
    Eigen::Vector3f getIntersectedPoint() { return point; };
    Eigen::Vector3f getIntersectedNormal() { return normal; };
    Shape *getIntersectedShape() { return intersectedShape; };
};

#endif /* Ray_h */
