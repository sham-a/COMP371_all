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
    Eigen::Vector3f temp = topLeft + (x * delta) * r - (y * delta + delta/2) * up;
    Eigen::Vector3f temp2 = (temp - centre).normalized();
    Ray ray(centre, temp2);
    return ray;
}

void Camera::setAntialiasing(bool anti, int rpp, int grid) {
    antialiasing = anti;
    raysperpixel = rpp;
    gridSize = grid;
}

void Camera::writeColor(Eigen::Vector3f color) {
    char colors[3];
    for (int i = 0; i < 3; i++) {
        colors[i] = char(static_cast<char>(255.999 * color[i]));
    }
    file.write(colors, 3);
}

void Camera::writeFile(std::vector<Eigen::Vector3f> buffer) {
    file.open(filename, std::ios_base::binary);
    file << "P6" << std::endl << dimx << ' ' << dimy << std::endl << "255" << std::endl;
    for (int i = 0; i < dimx; i ++) {
        for (int j = 0; j < dimy; j++) {
            writeColor(buffer[j*dimx + i]);
        }
    }
    file.close();
}
