#include "Sphere.h"
#include <cmath>

//constructor
Sphere::Sphere() : name(), position(), scaling(1, 1, 1), material(), transform(), invTransform(), invTranspose() {}

// compute the transformations
void Sphere::computeTransform() {
    Matrix4x4 scaleMat = Matrix4x4::scaling(scaling.x, scaling.y, scaling.z);
    Matrix4x4 transMat = Matrix4x4::translation(position.x, position.y, position.z);
    transform = transMat * scaleMat;
    invTransform = transform.inverse();
    invTranspose = invTransform.transpose();
}

// determine if ray intersects with sphere
bool Sphere::intersect(const Ray& ray, float& t, Vector3& normal) const {
    // transform the ray into object space using inverse transform
    Vector3 rayOriginOS = invTransform.transformPoint(ray.origin);
    Vector3 rayDirOS = invTransform.transformVector(ray.direction);
    rayDirOS.normalize();

    // Ray-sphere intersection in object space
    float a = rayDirOS.dot(rayDirOS);
    float b = 2.0f * rayDirOS.dot(rayOriginOS);
    float c = rayOriginOS.dot(rayOriginOS) - 1.0f;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return false;

    float sqrtDisc = sqrt(discriminant);
    float t0 = (-b - sqrtDisc) / (2 * a);
    float t1 = (-b + sqrtDisc) / (2 * a);

    float tSphere = (t0 > 0) ? t0 : t1;
    if (tSphere < 0) return false;

    // compute intersection point in object space
    Vector3 hitPointOS = rayOriginOS + rayDirOS * tSphere;

    // compute normal in object space
    Vector3 normalOS = hitPointOS;

    // transform normal back to world space
    normal = invTranspose.transformVector(normalOS);
    normal.normalize();

    // transform intersection point back to world space
    Vector3 hitPointWS = transform.transformPoint(hitPointOS);

    // compute t in world space
    t = (hitPointWS - ray.origin).length();

    return true;
}
