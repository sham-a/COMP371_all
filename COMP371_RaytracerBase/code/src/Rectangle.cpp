//
//  Rectangle.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <Eigen/Core>
#include <iostream>
#include "Rectangle.h"
#include "Ray.h"

Rectangle::Rectangle(std::string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d) : Shape(type) {
    this->p1 = a;
    this->p2 = b;
    this->p3 = c;
    this->p4 = d;
}

void Rectangle::determineN() {
    Eigen::Vector3f temp = (p2 - p1).cross(p3 - p1);
    this->n = temp.normalized();
    std::cout << "norm is: \n" << n << std::endl;
}

