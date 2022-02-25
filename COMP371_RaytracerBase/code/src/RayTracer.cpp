//
//  RayTracer.cpp
//  
//
//  Created by Ayah Shamma on 2022-02-01.
//

#include "RayTracer.h"
#include "../external/simpleppm.h"
#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

RayTracer::RayTracer(nlohmann::json j){
    this->j = j;
}

void RayTracer::run() {
    readJSON();
    
}

void RayTracer::readJSON() {
    for (auto itr = this->j["geometry"].begin(); itr!= this->j["geometry"].end(); itr++) {
        string type;
        if(itr->contains("type")) {
            type = (*itr)["type"].get<string>();
            if (type == "sphere"){
                cout << "it's a sphere" << endl;
                Eigen::Vector3f c(0, 0, 0);
                int i = 0;
                for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
                    if(i<3){
                        c[i++] = (*itr2).get<float>();
                    }
                }
                int r =(*itr)["radius"].get<int>();
                this->shape = new Sphere(type, r, c);
            }
            else if (type == "rectangle"){
                cout << "it's a rectanlge" << endl;
                Eigen::Vector3f p1(0, 0, 0);
                Eigen::Vector3f p2(0, 0, 0);
                Eigen::Vector3f p3(0, 0, 0);
                Eigen::Vector3f p4(0, 0, 0);
                
                int i = 0;
                for (auto itr2=(*itr)["p1"].begin(); itr2!= (*itr)["p1"].end(); itr2++){
                    if(i<3) { p1[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2=(*itr)["p2"].begin(); itr2!= (*itr)["p2"].end(); itr2++){
                    if(i<3) { p2[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2=(*itr)["p3"].begin(); itr2!= (*itr)["p3"].end(); itr2++){
                    if(i<3) { p3[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2=(*itr)["p4"].begin(); itr2!= (*itr)["p4"].end(); itr2++){
                    if(i<3) { p4[i++] = (*itr2).get<float>(); }
                }
                
                this->shape = new Rectangle(type, p1, p2, p3, p4);
            }
            else {
                cout << "it is not a sphere or rectangle, it is a: " << type << endl;
            }
        }
    }
}

// RAY CLASS
Ray::Ray(Point p, Eigen::Vector3f d) {
    this->origin = p;
    this->dir = d;
}
Point Ray::atPos(double t) {
    Point p = this->origin + t * this->dir;
    return p;
}

// SHAPE CLASS
Shape::Shape(string shape){
    this->shapeType = shape;
}

// SPHERE CLASS
Sphere::Sphere(string type, double r, Eigen::Vector3f c) : Shape(type){
    this->radius = r;
    this->centre = c;
}

bool Sphere::intersected(Ray ray){
    float a = ray.getDirection().dot(ray.getDirection());
    float b = 2 * ray.getDirection().dot(ray.getOrigin() - this->centre);
    float c = (ray.getOrigin() - this->centre).dot((ray.getOrigin() - this->centre)) - this->radius;
    float points = quadFormula(a, b, c);
    if (points == 0){
        return false;
    }
    return true;
}

float Sphere::quadFormula(float &a, float &b, float &c){
    float discr = b * b - 4 * a * c;
    // no real solution
    if (discr < 0) {
        return 0;
    }
    // one real solution
    else if (discr == 0) {
        float x0 = -b / (2 * a);
        return 1;
    }
    // two real solutions
    else {
        float x [2];
        float x1 = (-b + discr) / (2*a);
        float x2 = (-b - discr) / (2*a);
        if (x1 < x2) {
            x[0] = x1;
            x[1] = x2;
        }
        else {
            x[0] = x2;
            x[1] = x1;
        }
        return 2;
    }
}

// RECTANGLE CLASS
Rectangle::Rectangle(string type, Eigen::Vector3f a, Eigen::Vector3f b, Eigen::Vector3f c, Eigen::Vector3f d) : Shape(type) {
    this->p1 = a;
    this->p2 = b;
    this->p3 = c;
    this->p4 = d;
}
