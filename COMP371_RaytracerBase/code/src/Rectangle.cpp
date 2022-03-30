//
//  Rectangle.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include "Rectangle.h"
#include "Ray.h"
using namespace std;

Rectangle::Rectangle(std::string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d,
                     float ka, float kd, float ks, Eigen::Vector3f ac, Eigen::Vector3f dc, Eigen::Vector3f sc, float pc)
                     : Shape(type, ka, kd, ks, ac, dc, sc, pc), p1(a), p2(b), p3(c), p4(d) {
    Eigen::Vector3f temp = (p2 - p1).cross(p3 - p1);
    n = temp.normalized();
    v12 = p2 - p1;
    v23 = p3 - p2;
    v34 = p4 - p3;
    v41 = p1 - p4;
}
bool Rectangle::intersected(Ray *ray) {
    if(n.dot(ray->getDirection()) == 0) {
        return false;
    }
    float t = (n.dot(p1 - ray->getOrigin()))/(n.dot(ray->getDirection()));
//    if(t < 0) {
//        return false;
//    }

    Eigen::Vector3f p = ray->atPos(t);

    Eigen::Vector3f pP1 = p - p1;
    Eigen::Vector3f pP2 = p - p2;
    Eigen::Vector3f pP3 = p - p3;
    Eigen::Vector3f pP4 = p - p4;

    bool signs[4] = { (v12.cross(pP1)).dot(n) > 0,
                      (v23.cross(pP2)).dot(n) > 0,
                      (v34.cross(pP3)).dot(n) > 0,
                      (v41.cross(pP4)).dot(n) > 0 };
    if (signs[0] && signs[1] && signs[2] && signs[3]) {
        ray->setClosestShape(t, this, p, n);
        return true;
    }
    else if (!signs[0] && !signs[1] && !signs[2] && !signs[3]) {
        ray->setClosestShape(t, this, p, n);
        return true;
    }
    return false;
}