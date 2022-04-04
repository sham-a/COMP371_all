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
    Eigen::Vector3f v12;
    Eigen::Vector3f v23;
    Eigen::Vector3f v34;
    Eigen::Vector3f v41;
public:
    Rectangle(std::string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d, float ka,
              float kd, float ks, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc, float pc);
    void intersected(Ray *ray) override;

    ~Rectangle() = default;
};

#endif /* Rectangle_h */
