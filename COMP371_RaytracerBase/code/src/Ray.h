//
//  Ray.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Ray_h
#define Ray_h

#include <Eigen/Core>
#include <Eigen/Dense>

class Ray {
    Eigen::Vector3f origin;           // origin of ray vector
    Eigen::Vector3f dir;    // direction of ray vector
public:
    Ray(Eigen::Vector3f p, Eigen::Vector3f d);
    Eigen::Vector3f atPos(double t);
    Eigen::Vector3f getDirection() { return dir; };
    Eigen::Vector3f getOrigin() { return origin; };
};

#endif /* Ray_h */
