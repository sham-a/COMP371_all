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
#include "Sphere.h"
#include "Rectangle.h"
#include "Ray.h"


using namespace std;

RayTracer::RayTracer(nlohmann::json j){
    this->j = j;
}

void RayTracer::run() {
    readJSON();
    
    cout << "I am officially a " << shape->getShape() << endl;
    
    std::vector<double> buffer(3*dimx*dimy);
    for(int j=0;j<dimy;++j){
        for(int i=0;i<dimx;++i){
            Eigen::Vector3f dir = createDirVector(i, j);
            Ray *ray = new Ray(o, dir);
            auto r = 1;
            auto g = 1;
            auto b = 1;
            if (shape->intersected(*ray)){
                r = ac[0];
                g = ac[1];
                b = ac[2];
            }

            buffer[3*j*dimx+3*i+0]= r;
            buffer[3*j*dimx+3*i+1]= g;
            buffer[3*j*dimx+3*i+2]= b;
        }
    }
    save_ppm("test.ppm", buffer, dimx, dimy);
}

void RayTracer::readJSON() {
    for (auto itr = j["geometry"].begin(); itr!= j["geometry"].end(); itr++) {
        // Initializing the shape
        string type;
        if(itr->contains("type")) {
            type = (*itr)["type"].get<string>();
            if (type == "sphere"){
                Eigen::Vector3f c(0, 0, 0);
                int i = 0;
                for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
                    if(i<3){
                        c[i++] = (*itr2).get<float>();
                    }
                }
                int r =(*itr)["radius"].get<int>();
                shape = new Sphere(type, r, c);
            }
            else if (type == "rectangle"){
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
                
                shape = new Rectangle(type, p1, p2, p3, p4);
            }
            else {
                cout << "it is not a sphere or rectangle, it is a: " << type << endl;
            }
        }
        // Reading the color values
        int i = 0;
        for (auto itr2 =(*itr)["ac"].begin(); itr2!= (*itr)["ac"].end(); itr2++){
            if(i<3){ ac[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 =(*itr)["dc"].begin(); itr2!= (*itr)["dc"].end(); itr2++){
            if(i<3){ dc[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 =(*itr)["sc"].begin(); itr2!= (*itr)["sc"].end(); itr2++){
            if(i<3){ sc[i++] = (*itr2).get<float>(); }
        }
    }
    for (auto itr = j["output"].begin(); itr!= j["output"].end(); itr++) {
        if(itr->contains("filename")) {
            int i = 0;
            for (auto itr2 =(*itr)["size"].begin(); itr2!= (*itr)["size"].end(); itr2++){
                if(i == 0) { dimx = (*itr2).get<int>(); }
                if(i == 1) { dimy = (*itr2).get<int>(); }
                i++;
            }
            i = 0;
            for (auto itr2 =(*itr)["lookat"].begin(); itr2!= (*itr)["lookat"].end(); itr2++){
                if(i<3) { l[i++] = (*itr2).get<float>(); }
            }
            i = 0;
            for (auto itr2 =(*itr)["up"].begin(); itr2!= (*itr)["up"].end(); itr2++){
                if(i<3) { u[i++] = (*itr2).get<float>(); }
            }
            fov = (double)(*itr)["fov"].get<int>();
            fov *= M_PI / 180;      // set it to radians
            i = 0;
            for (auto itr2 =(*itr)["centre"].begin(); itr2!= (*itr)["centre"].end(); itr2++){
                if(i<3){
                    o[i++] = (*itr2).get<float>();
                }
            }
        }
    }
}
Eigen::Vector3f RayTracer::createDirVector(int i, int j){
    double delta = 2 * tan(fov/2) / dimy;
//    cout << delta << endl;
    Eigen::Vector3f r = l.cross(u);
    Eigen::Vector3f A = o + l;
    Eigen::Vector3f B = A + tan(fov/2) * u;
    Eigen::Vector3f C = B - dimx * delta * r / 2;
    Eigen::Vector3f p = C + (j * delta + delta/2) * r - (i * delta + delta/2) * u;
    Eigen::Vector3f dir = p.normalized() - o;
//    cout << fov << ", "<< dimy << endl;
    return dir;
}
