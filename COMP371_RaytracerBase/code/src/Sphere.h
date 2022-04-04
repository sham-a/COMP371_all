//
//  Sphere.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Sphere_h
#define Sphere_h

#include <Eigen/Core>
#include "Shape.h"

class Sphere : public Shape {
    double radius;
    Eigen::Vector3f centre;
    float rSquared;
public:
    Sphere(std::string type, double r, Eigen::Vector3f c, float ka, float kd, float ks, Eigen::Vector3f ac, Eigen::Vector3f dc,
           Eigen::Vector3f sc, float pc);
    virtual Eigen::Vector3f get_centre() { return centre; };
    void intersected(Ray *ray) override;
    float quadFormula(float a, float b, float c);
    ~Sphere() = default;
};

#endif /* Sphere_h */
