//
//  Light.cpp
//  
//
//  Created by Ayah Shamma on 2022-03-12.
//

#include <iostream>
#include <Eigen/Core>
#include <math.h>
#include "Light.h"
#include "Ray.h"

using namespace std;

Light::Light(string type, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s)
        : type(type), lid(lid), is(is), shapes(s) {}



PointLight::PointLight(string type, Eigen::Vector3f centre, Eigen::Vector3f lid, Eigen::Vector3f is, vector<Shape *> s)
        : Light(type, lid, is, s), centre(centre) {}

Eigen::Vector3f PointLight::cast_light(Ray *ray) {
    // generating shadow ray
    Eigen::Vector3f direction = (centre - ray->getIntersectedPoint()).normalized();
    Ray shadowRay(centre, -direction);
    for (Shape *s: shapes) {
        s->intersected(&shadowRay);
    }
    if (ray->getIntersectedShape() != shadowRay.getIntersectedShape()) {
        return Eigen::Vector3f(0, 0, 0);
    } else {
        // create the diffuse color
        Eigen::Vector3f temp = shadowRay.getIntersectedShape()->getKd() * shadowRay.getIntersectedShape()->getDc();
        Eigen::Vector3f diffuse;
        if (shadowRay.getIntersectedNormal().dot(direction) < 0) diffuse = Eigen::Vector3f(0, 0, 0);
        else {
            diffuse = Eigen::Vector3f(temp.x() * getLid().x(),
                                      temp.y() * getLid().y(),
                                      temp.z() * getLid().z());
            diffuse = diffuse * shadowRay.getIntersectedNormal().dot(direction);
        }
        //clamp(&diffuse);
        // create the specular color
        Eigen::Vector3f H = (direction - ray->getDirection()).normalized();
        float temp2 = H.dot(ray->getIntersectedNormal());
        temp2 = temp2 < 0 ? 0 : (temp2 > 1 ? 1 : temp2);
        Eigen::Vector3f temp3 = shadowRay.getIntersectedShape()->getKs() * shadowRay.getIntersectedShape()->getSc();
        Eigen::Vector3f specular = Eigen::Vector3f(temp3.x() * getIs().x(),
                                                   temp3.y() * getIs().y(),
                                                   temp3.z() * getIs().z()) *
                                   pow(temp2, shadowRay.getIntersectedShape()->getPc());
        return diffuse + specular;
    }
}

void PointLight::clamp(Eigen::Vector3f *v) {
    v->x() = v->x() < 0 ? 0 : (v->x() > 1 ? 1 : v->x());
    v->y() = v->y() < 0 ? 0 : (v->y() > 1 ? 1 : v->y());
    v->z() = v->z() < 0 ? 0 : (v->z() > 1 ? 1 : v->z());
}