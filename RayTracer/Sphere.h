#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "Matrix4x4.h"
#include <string>

/**
 * Class for sphere in the scene.
 * Handles properites of sphere aswell as intersections with rays.
 */

class Sphere {
public:
    std::string name;
    Vector3 position;
    Vector3 scaling;
    Material material;

    Matrix4x4 transform;        // transformation matrix
    Matrix4x4 invTransform;     // inverse transformation matrix
    Matrix4x4 invTranspose;     // inverse transpose matrix for normals

    // Constructor
    Sphere();

    void computeTransform();

    // Ray-sphere intersection in object space
    bool intersect(const Ray& ray, float& t, Vector3& normal) const;
};

#endif 
