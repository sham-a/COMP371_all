//
//  Shape.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <string>
#include <Eigen/Core>
#include "Shape.h"
#include "Ray.h"

Shape::Shape(std::string shape, float ka, float kd, float ks, Eigen::Vector3f ac, Eigen::Vector3f dc,
             Eigen::Vector3f sc, float pc)
             : shapeType(shape), ka(ka), kd(kd), ks(ks), ac(ac), dc(dc), sc(sc), pc(pc) {}