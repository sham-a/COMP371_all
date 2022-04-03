//
//  Light.h
//  
//
//  Created by Ayah Shamma.
//

#ifndef Light_h
#define Light_h

#include <string>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "Shape.h"

using namespace std;

class Light {
    string type;
    Eigen::Vector3f lid;
    Eigen::Vector3f is;
protected:
    vector<Shape *> shapes;
public:
    Light(string type, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s);
    string get_type() { return type; };
    Eigen::Vector3f getLid() { return lid; };
    Eigen::Vector3f getIs() { return is; };
    virtual Eigen::Vector3f cast_light(Ray *ray) = 0;
};

class PointLight : public Light {
    Eigen::Vector3f centre;
public:
    PointLight(string type, Eigen::Vector3f centre, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s);
    Eigen::Vector3f cast_light(Ray *ray) override;
    static void clamp(Eigen::Vector3f *v);
};
#endif /* Light_h */
