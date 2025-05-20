#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// parse input file
Scene parseInputFile(const std::string& filename) {
    Scene scene;
    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "Cannot open input file: " << filename << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(infile, line)) {
        // remove comments and empty lines
        if (line.empty() || line[0] == '#') continue;
        std::istringstream iss(line);
        std::string keyword;
        iss >> keyword;
        std::transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);
        if (keyword == "NEAR") {
            iss >> scene.nearPlane;
        } else if (keyword == "LEFT") {
            iss >> scene.left;
        } else if (keyword == "RIGHT") {
            iss >> scene.right;
        } else if (keyword == "BOTTOM") {
            iss >> scene.bottom;
        } else if (keyword == "TOP") {
            iss >> scene.top;
        } else if (keyword == "RES") {
            iss >> scene.resX >> scene.resY;
        } else if (keyword == "SPHERE") {
            Sphere sphere;
            iss >> sphere.name;
            iss >> sphere.position.x >> sphere.position.y >> sphere.position.z;
            iss >> sphere.scaling.x >> sphere.scaling.y >> sphere.scaling.z;
            iss >> sphere.material.color.r >> sphere.material.color.g >> sphere.material.color.b;
            iss >> sphere.material.Ka >> sphere.material.Kd >> sphere.material.Ks >> sphere.material.Kr >> sphere.material.specExp;
            sphere.computeTransform(); 
            scene.spheres.push_back(sphere);
        } else if (keyword == "LIGHT") {
            Light light;
            iss >> light.name;
            iss >> light.position.x >> light.position.y >> light.position.z;
            iss >> light.intensity.r >> light.intensity.g >> light.intensity.b;
            scene.lights.push_back(light);
        } else if (keyword == "BACK") {
            iss >> scene.backgroundColor.r >> scene.backgroundColor.g >> scene.backgroundColor.b;
        } else if (keyword == "AMBIENT") {
            iss >> scene.ambientLight.r >> scene.ambientLight.g >> scene.ambientLight.b;
        } else if (keyword == "OUTPUT") {
            iss >> scene.outputFileName;
        }
    }
    infile.close();
    return scene;
}
