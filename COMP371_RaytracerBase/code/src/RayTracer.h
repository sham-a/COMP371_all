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
#include "Shape.h"
#include "Light.h"
#include "Camera.h"

using namespace nlohmann;
using namespace std;

class RayTracer {
    vector<Shape *> shapes;
    vector<Light *> lights;
    vector<Camera *> cameras;
    nlohmann::json json;
    
public:
    RayTracer(nlohmann::json j);
    void run();
    void readJSON();
    void clamp(Eigen::Vector3f *v);

    ~RayTracer();
};




#endif /* RayTracer_h */
