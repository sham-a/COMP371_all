//
//  Camera.h
//
//
//  Created by Ayah Shamma.
//

#ifndef Camera_h
#define Camera_h
#include <Eigen/Core>
#include "Ray.h"

class Camera {
    std::string filename;
    int dimx;
    int dimy;
    Eigen::Vector3f lookAt;
    Eigen::Vector3f up;
    Eigen::Vector3f centre;
    float fov;
    Eigen::Vector3f ai;
    Eigen::Vector3f bkc;

    Eigen::Vector3f r;
    float delta;
    Eigen::Vector3f topLeft;
public:
    Camera(std::string f, int width, int height, Eigen::Vector3f l, Eigen::Vector3f u, Eigen::Vector3f c, float fov,
           Eigen::Vector3f ai, Eigen::Vector3f bkc);
    Ray create_ray(float x, float y);
    std::string &getFilename() { return filename; };
    int getDimx() const { return dimx; };
    int getDimy() const { return dimy; };
    Eigen::Vector3f &getLookAt() { return lookAt; };
    Eigen::Vector3f &getUp() { return up; };
    Eigen::Vector3f &getCentre() { return centre; };
    float getFov() { return fov; };
    Eigen::Vector3f &getAi() { return ai; };
    Eigen::Vector3f &getBkc() { return bkc; };
};

#endif /* Camera_h */
