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
#include <sstream>
#include <string>
#include <vector>
#include "Sphere.h"
#include "Rectangle.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.h"

using namespace std;

RayTracer::RayTracer(nlohmann::json j) : json(j) {}

void RayTracer::run() {
    readJSON();
    cout << "Finished reading JSON, running the Ray Tracer..." << endl;
    for (Camera *cam: cameras) {
//        std::vector<Eigen::Vector3f> buffer(cam->getDimx() * cam->getDimy());
        std::vector<double> buffer(3 * cam->getDimx() * cam->getDimy());
        for (int j = 0; j < cam->getDimy(); ++j) {
            for (int i = 0; i < cam->getDimx(); ++i) {

                Eigen::Vector3f temp(0, 0, 0);

                for (int gX = 0; gX < cam->getGridSize(); gX++) {
                    for (int gY = 0; gY < cam->getGridSize(); gY++) {
                        for (int rayNum = 0; rayNum < cam->getRPP(); rayNum++) {
                            // delta used for the calculation of the pixels center within the grid
                            float gridDelta = 1.0 / cam->getGridSize();
                            Ray ray = cam->create_ray(i + gX * gridDelta, j + gY * gridDelta);
                            if (gridDelta == 1 && cam->getRPP() == 1) // if the grid is 1x1 and there is only 1 rpp
                            {
                                // hit the center of the pixel
                                ray = cam->create_ray(i + 0.5f, j + 0.5f);
                            }
                            for (Shape *shape: shapes) {
                                shape->intersected(&ray);
                            }
                            if (ray.getIntersectedShape() == nullptr) {
                                temp.x() += cam->getBkc().x();
                                temp.y() += cam->getBkc().y();
                                temp.z() += cam->getBkc().z();
                            } else {
                                Eigen::Vector3f temp1(0, 0, 0);
                                for (Light *light: lights) {
                                    Eigen::Vector3f color = light->cast_light(&ray);
                                    temp1.x() += color.x();
                                    temp1.y() += color.y();
                                    temp1.z() += color.z();
                                }
                                temp1 += Eigen::Vector3f(cam->getAi().x() * ray.getIntersectedShape()->getAc().x(),
                                                         cam->getAi().y() * ray.getIntersectedShape()->getAc().y(),
                                                         cam->getAi().z() * ray.getIntersectedShape()->getAc().z())
                                         * ray.getIntersectedShape()->getKa();
                                clamp(&temp1);
                                temp.x() += temp1.x();
                                temp.y() += temp1.y();
                                temp.z() += temp1.z();
                            }
                        }
                    }
                }
                temp = temp / (cam->getGridSize() * cam->getGridSize() * cam->getRPP());
                clamp(&temp);
//                buffer[j * cam->getDimx() + i] = temp;
                buffer[3 * j * cam->getDimx() + 3 * i + 0] = temp.x();
                buffer[3 * j * cam->getDimx() + 3 * i + 1] = temp.y();
                buffer[3 * j * cam->getDimx() + 3 * i + 2] = temp.z();
            }
        }
        cout << "Saving as ppm..." << endl;

        save_ppm(cam->getFilename(), buffer, cam->getDimx(), cam->getDimy());
//        cam->writeFile(buffer);
    }
}

void RayTracer::readJSON() {
    cout << "Reading JSON..." << endl;
    for (auto itr = json["geometry"].begin(); itr != json["geometry"].end(); itr++) {
        // Reading the color values
        float ka = (*itr)["ka"].get<float>();
        float kd = (*itr)["kd"].get<float>();
        float ks = (*itr)["ks"].get<float>();
        float pc = (*itr)["pc"].get<float>();
        Eigen::Vector3f ac(0,0,0);
        Eigen::Vector3f dc(0,0,0);
        Eigen::Vector3f sc(0,0,0);
        int i = 0;
        for (auto itr2 = (*itr)["ac"].begin(); itr2 != (*itr)["ac"].end(); itr2++) {
            if (i < 3) { ac[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["dc"].begin(); itr2 != (*itr)["dc"].end(); itr2++) {
            if (i < 3) { dc[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["sc"].begin(); itr2 != (*itr)["sc"].end(); itr2++) {
            if (i < 3) { sc[i++] = (*itr2).get<float>(); }
        }
        // Creating the shapes
        string type;
        if (itr->contains("type")) {
            type = (*itr)["type"].get<string>();
            if (type == "sphere") {
                Eigen::Vector3f c(0, 0, 0);
                int i = 0;
                for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
                    if (i < 3) {
                        c[i++] = (*itr2).get<float>();
                    }
                }
                int r = (*itr)["radius"].get<int>();
                Shape *shape = new Sphere(type, r, c, ka, kd, ks, ac, dc, sc, pc);
                shapes.push_back(shape);
            } else if (type == "rectangle") {
                Eigen::Vector3f p1(0, 0, 0);
                Eigen::Vector3f p2(0, 0, 0);
                Eigen::Vector3f p3(0, 0, 0);
                Eigen::Vector3f p4(0, 0, 0);

                int i = 0;
                for (auto itr2 = (*itr)["p1"].begin(); itr2 != (*itr)["p1"].end(); itr2++) {
                    if (i < 3) { p1[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2 = (*itr)["p2"].begin(); itr2 != (*itr)["p2"].end(); itr2++) {
                    if (i < 3) { p2[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2 = (*itr)["p3"].begin(); itr2 != (*itr)["p3"].end(); itr2++) {
                    if (i < 3) { p3[i++] = (*itr2).get<float>(); }
                }
                i = 0;
                for (auto itr2 = (*itr)["p4"].begin(); itr2 != (*itr)["p4"].end(); itr2++) {
                    if (i < 3) { p4[i++] = (*itr2).get<float>(); }
                }

                Shape *shape = new Rectangle(type, p1, p2, p3, p4, ka, kd, ks, ac, dc, sc, pc);
                shapes.push_back(shape);
            } else {
                cout << "it is not a sphere or rectangle, it is a: " << type << endl;
            }
            cout << "Created shape object of type: " << type << endl;
        }
    }
    // Creating the lights
    for (auto itr = json["light"].begin(); itr != json["light"].end(); itr++) {
        string type = (*itr)["type"].get<string>();
        Eigen::Vector3f lightCentre(0,0,0);
        Eigen::Vector3f lid(0,0,0);
        Eigen::Vector3f is(0,0,0);
        int i = 0;
        for (auto itr2 = (*itr)["id"].begin(); itr2 != (*itr)["id"].end(); itr2++) {
            if (i < 3) { lid[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["is"].begin(); itr2 != (*itr)["is"].end(); itr2++) {
            if (i < 3) { is[i++] = (*itr2).get<float>(); }
        }
        if (type == "area") {
            Eigen::Vector3f p1(0,0,0);
            i = 0;
            for (auto itr2 = (*itr)["p1"].begin(); itr2 != (*itr)["p1"].end(); itr2++) {
                if (i < 3) { p1[i++] = (*itr2).get<float>(); }
            }
            Eigen::Vector3f p2(0,0,0);
            i = 0;
            for (auto itr2 = (*itr)["p2"].begin(); itr2 != (*itr)["p2"].end(); itr2++) {
                if (i < 3) { p2[i++] = (*itr2).get<float>(); }
            }
            Eigen::Vector3f p3(0,0,0);
            i = 0;
            for (auto itr2 = (*itr)["p3"].begin(); itr2 != (*itr)["p3"].end(); itr2++) {
                if (i < 3) { p3[i++] = (*itr2).get<float>(); }
            }
            Eigen::Vector3f p4(0,0,0);
            i = 0;
            for (auto itr2 = (*itr)["p4"].begin(); itr2 != (*itr)["p4"].end(); itr2++) {
                if (i < 3) { p4[i++] = (*itr2).get<float>(); }
            }

            lightCentre = Eigen::Vector3f((p3.x() - p1.x())/2, (p3.y() - p1.y())/2, (p3.z() - p1.z())/2);
        }
        if (type == "point") {
            i = 0;
            for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
                if (i < 3) { lightCentre[i++] = (*itr2).get<float>(); }
            }
        }
        Light *light = new PointLight(type, lightCentre, lid, is, shapes);
        lights.push_back(light);
        cout << "Created light object." << endl;
    }
    // Creating the cameras
    for (auto itr = json["output"].begin(); itr != json["output"].end(); itr++) {
        string filename = (*itr)["filename"].get<string>();
        int dimx;
        int dimy;
        Eigen::Vector3f o(0,0,0);
        Eigen::Vector3f l(0,0,0);
        Eigen::Vector3f u(0,0,0);
        float fov;
        Eigen::Vector3f ai(0,0,0);
        Eigen::Vector3f bkc(0,0,0);
        int i = 0;
        for (auto itr2 = (*itr)["size"].begin(); itr2 != (*itr)["size"].end(); itr2++) {
            if (i == 0) { dimx = (*itr2).get<int>(); }
            if (i == 1) { dimy = (*itr2).get<int>(); }
            i++;
        }
        i = 0;
        for (auto itr2 = (*itr)["lookat"].begin(); itr2 != (*itr)["lookat"].end(); itr2++) {
            if (i < 3) { l[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["up"].begin(); itr2 != (*itr)["up"].end(); itr2++) {
            if (i < 3) { u[i++] = (*itr2).get<float>(); }
        }
        fov = (float) (*itr)["fov"].get<int>();
        fov *= M_PI / 180;      // set it to radians
        i = 0;
        for (auto itr2 = (*itr)["centre"].begin(); itr2 != (*itr)["centre"].end(); itr2++) {
            if (i < 3) { o[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["bkc"].begin(); itr2 != (*itr)["bkc"].end(); itr2++) {
            if (i < 3) { bkc[i++] = (*itr2).get<float>(); }
        }
        i = 0;
        for (auto itr2 = (*itr)["ai"].begin(); itr2 != (*itr)["ai"].end(); itr2++) {
            if (i < 3) { ai[i++] = (*itr2).get<float>(); }
        }
        bool anti = false;
        int rpp = 1;
        int grid = 1;
        if (itr->contains("antialiasing") && (*itr)["antialiasing"].get<bool>()) {
            cout << "... with antialiasing" << endl;
            anti = true;
            i = 0;
            for (auto itr2 = (*itr)["raysperpixel"].begin(); itr2 != (*itr)["raysperpixel"].end(); itr2++) {
                if ( i == 0 ) {
                    rpp = (*itr2).get<float>();
                    i++;
                }
                else if ( i == 1 ) {
                    grid = rpp;
                    rpp = (*itr2).get<float>();
                }
            }
        }

        Camera *cam = new Camera(filename, dimx, dimy, l, u, o, fov, ai, bkc);
        cam->setAntialiasing(anti, rpp, grid);
        cameras.push_back(cam);
        cout << "Created camera object." << endl;
    }
}

void RayTracer::clamp(Eigen::Vector3f *v) {
    v->x() = v->x() < 0 ? 0 : (v->x() > 1 ? 1 : v->x());
    v->y() = v->y() < 0 ? 0 : (v->y() > 1 ? 1 : v->y());
    v->z() = v->z() < 0 ? 0 : (v->z() > 1 ? 1 : v->z());
}

RayTracer::~RayTracer() {
    for (auto s : shapes) {
        delete s;
    }
    for (auto l : lights) {
        delete l;
    }
    for (auto c : cameras) {
        delete c;
    }
}