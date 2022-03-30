//
//  Camera.cpp
//
//
//  Created by Ayah Shamma.
//

#include "Camera.h"
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>

Camera::Camera(std::string f, int width, int height, Eigen::Vector3f l, Eigen::Vector3f u, Eigen::Vector3f c,
               float fov, Eigen::Vector3f ai, Eigen::Vector3f bkc)
               : filename(f), dimx(width), dimy(height), lookAt(l), up(u), centre(c), fov(fov), ai(ai), bkc(bkc) {

    delta = 2 * tan(fov/2) / dimy;
    r = lookAt.cross(up);
    Eigen::Vector3f A = centre + lookAt;
    Eigen::Vector3f B = A + tan(fov/2) * up;
    topLeft = B - dimx * delta * r / 2;
}
Ray Camera::create_ray(float x, float y) {
    if(x == 301 && y == 140) {
        std::cout << "       ** creating cast light" << std::endl;
    }
    Eigen::Vector3f temp = topLeft + (x * delta + delta/2) * r - (y * delta + delta/2) * up;
    Eigen::Vector3f temp2 = (temp - centre)/(temp - centre).norm();
    Ray ray(centre, temp2);
    return ray;
}
