//
//  Light.cpp
//  
//
//  Created by Ayah Shamma on 2022-03-12.
//

#include <iostream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <math.h>
#include "Light.h"
#include "Ray.h"

using namespace std;

Light::Light(string type, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s)
: type(type), lid(lid), is(is), shapes(s) {}

PointLight::PointLight(string type, Eigen::Vector3f centre, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s)
: Light(type, lid, is, s), centre(centre) {}

Eigen::Vector3f PointLight::cast_light(Ray *ray, int x, int y) {
    // generating shadow ray
//    cout << "   ** generating shadow ray **" << endl;
    Eigen::Vector3f direction = (ray->getIntersectedPoint() - centre).normalized();
    Ray *shadowRay = new Ray(centre, direction);
    bool hit;
    for (Shape *s : shapes) {
        hit = s->intersected(shadowRay);
        if (hit) {
            if (ray->getIntersectedShape() != shadowRay->getIntersectedShape()) {
                return Eigen::Vector3f{0, 0, 0};
            } else {
//    cout << "   ** creating colors **" << endl;
                Eigen::Vector3f ambient = shadowRay->getIntersectedShape()->getAc() * shadowRay->getIntersectedShape()->getKa();
//    cout << "       ** created ambient **" << endl;
                // create the diffuse color
                Eigen::Vector3f diffuse =
                        shadowRay->getIntersectedShape()->getKd() * shadowRay->getIntersectedShape()->getDc() *
                        (shadowRay->getIntersectedNormal().dot(-shadowRay->getDirection()));
                clamp(&diffuse);
//    cout << "       ** created diffuse **" << endl;
                // create the specular color
                Eigen::Vector3f R = 2 * shadowRay->getIntersectedNormal() *
                                    (shadowRay->getIntersectedNormal().dot(-shadowRay->getDirection())) -
                                    shadowRay->getDirection();
                Eigen::Vector3f H = (shadowRay->getDirection() + ray->getDirection()).normalized();
                Eigen::Vector3f specular = shadowRay->getIntersectedShape()->getKs() * getIs() *
                                           max(pow(H.dot(ray->getIntersectedNormal()),
                                                   shadowRay->getIntersectedShape()->getPc()), (float) 0);
                clamp(&specular);
//    cout << "       ** created specular **" << endl;
                // create the final color
                Eigen::Vector3f color = diffuse + specular + ambient;
                clamp(&color);
//    cout << "   ** returning the color" << endl;
                return color;
            }
        }
    }
}

void PointLight::clamp(Eigen::Vector3f *v) {
    if (v->x() < 0){
        v->x() = 0;
    }
    else if (v->x() > 1){
        v->x() = 1;
    }
    if (v->y() < 0){
        v->y() = 0;
    }
    else if (v->y() > 1){
        v->y() = 1;
    }
    if (v->z() < 0){
        v->z() = 0;
    }
    else if (v->z() > 1){
        v->z() = 1;
    }
}