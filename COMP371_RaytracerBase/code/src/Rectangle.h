//
//  Rectangle.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Rectangle_h
#define Rectangle_h

#include <Eigen/Core>
#include "Shape.h"

class Rectangle : public Shape {
    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
    Eigen::Vector3f n;
public:
    Rectangle(std::string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d);
    void determineN();
};

#endif /* Rectangle_h */
