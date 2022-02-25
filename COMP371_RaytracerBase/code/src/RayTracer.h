//
//  RayTracer.h
//  
//
//  Created by Ayah Shamma on 2022-02-01.
//

#ifndef RayTracer_h
#define RayTracer_h

#include "../external/json.hpp"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <string>

using namespace nlohmann;
using namespace std;

typedef Eigen::Matrix<float, 3, 1> Point;

//forward declaration
class Shape;

class RayTracer {
    Shape *shape;           // main shape of the scene
    nlohmann::json j;
    int dimx;               // image width
    int dimy;               // image height
    Eigen::Vector3f o;      // camera center vector
    Eigen::Vector3f l;      // look-at vector
    Eigen::Vector3f u;      // up vector
    
public:
    RayTracer(nlohmann::json j);
    void run();
    void readJSON();
};

class Ray {
    Point origin;           // origin of ray vector
    Eigen::Vector3f dir;    // direction of ray vector
public:
    Ray(Point p, Eigen::Vector3f d);
    Point atPos(double t);
    Eigen::Vector3f getDirection() { return dir; };
    Point getOrigin() { return origin; };
};

class Shape {
    string shapeType;
public:
    Shape(string shape);
    string getShape() { return this->shapeType; };
};
class Sphere : public Shape {
    double radius;
    Eigen::Vector3f centre;
public:
    Sphere(string type, double r, Eigen::Vector3f c);
    bool intersected(Ray ray);
    float quadFormula(float &a, float &b, float &c);
};

class Rectangle : public Shape {
    Eigen::Vector3f p1;
    Eigen::Vector3f p2;
    Eigen::Vector3f p3;
    Eigen::Vector3f p4;
public:
    Rectangle(string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d);

};


#endif /* RayTracer_h */
