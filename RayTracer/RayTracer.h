#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "Scene.h"
#include "Color.h"

// traces a ray through the scene and computes the resulting color.
Color traceRay(const Ray& ray, const Scene& scene, int depth);

#endif
