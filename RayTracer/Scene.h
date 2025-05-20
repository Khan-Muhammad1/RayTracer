#ifndef SCENE_H
#define SCENE_H

#include "Sphere.h"
#include "Light.h"
#include "Color.h"
#include <vector>

/**
 * Scene class to hold all objects and light in the scene.
 */

class Scene {
public:
    // camera parameters
    float nearPlane;
    float left, right, top, bottom;
    int resX, resY;

    // scene elements
    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    // background and ambient
    Color backgroundColor;
    Color ambientLight;

    // output file name
    std::string outputFileName;

    Scene() : nearPlane(1), left(-1), right(1), top(1), bottom(-1),
              resX(800), resY(600), backgroundColor(), ambientLight(),
              outputFileName("output.ppm") {}
};

#endif
