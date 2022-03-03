//
//  Shape.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Shape_h
#define Shape_h

#include <string>

class Ray;

class Shape {
    std::string shapeType;
public:
    Shape(std::string shape);
    std::string getShape() { return this->shapeType; };
    virtual bool intersected(Ray ray);
};

#endif /* Shape_h */
