//
//  Shape.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Shape_h
#define Shape_h

#include <string>
#include <Eigen/Core>

class Ray;

class Shape {
    std::string shapeType;
    float ka;
    float kd;
    float ks;
    Eigen::Vector3f ac;
    Eigen::Vector3f dc;
    Eigen::Vector3f sc;
    float pc;
public:
    Shape(std::string shape, float ka, float kd, float ks, Eigen::Vector3f ac, Eigen::Vector3f dc,
          Eigen::Vector3f sc, float pc);
    virtual bool intersected(Ray *ray) = 0;
    std::string get_shape() { return this->shapeType; };
    float getKa() { return ka; };
    float getKd() { return kd; };
    float getKs() { return ks; };
    Eigen::Vector3f getAc() { return ac; };
    Eigen::Vector3f getDc() { return dc; };
    Eigen::Vector3f getSc() { return sc; };
    float getPc() { return pc; };
};

#endif /* Shape_h */
