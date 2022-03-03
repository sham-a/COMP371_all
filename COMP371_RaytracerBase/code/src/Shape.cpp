//
//  Shape.cpp
//  
//
//  Created by Ayah Shamma.
//

#include <stdio.h>
#include <string>
#include "Shape.h"
#include "Ray.h"

Shape::Shape(std::string shape){
    this->shapeType = shape;
}
bool Shape::intersected(Ray ray){
    return false;
}
