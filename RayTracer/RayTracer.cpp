#include "RayTracer.h"
#include <limits>


const int MAX_DEPTH = 5;

Color traceRay(const Ray& ray, const Scene& scene, int depth) {
    if (depth > MAX_DEPTH) return scene.backgroundColor;

    float closestT = std::numeric_limits<float>::max();
    const Sphere* closestSphere = nullptr;
    Vector3 hitNormal;

    // Find closest intersection
    for (const auto& sphere : scene.spheres) {
        float t;
        Vector3 normal;
        if (sphere.intersect(ray, t, normal)) {
            if (t < closestT) {
                closestT = t;
                closestSphere = &sphere;
                hitNormal = normal;
            }
        }
    }

    if (!closestSphere) return scene.backgroundColor;

    // compute intersection point
    Vector3 hitPoint = ray.origin + ray.direction * closestT;

    // initialize color with ambient term
    Color finalColor = closestSphere->material.color * closestSphere->material.Ka * scene.ambientLight;

    // for each light
    for (const auto& light : scene.lights) {
        Vector3 lightDir = light.position - hitPoint;
        float lightDist = lightDir.length();
        lightDir.normalize();

        // shadow check
        Ray shadowRay(hitPoint + hitNormal * 0.001f, lightDir);
        bool inShadow = false;
        for (const auto& sphere : scene.spheres) {
            if (&sphere == closestSphere) continue;
            float t;
            Vector3 normal;
            if (sphere.intersect(shadowRay, t, normal)) {
                if (t > 0 && t < lightDist) {
                    inShadow = true;
                    break;
                }
            }
        }
        if (inShadow) continue;

        // diffuse shading
        float NdotL = std::max(hitNormal.dot(lightDir), 0.0f);
        Color diffuse = closestSphere->material.color * closestSphere->material.Kd * NdotL;

        // specular shading
        Vector3 viewDir = -ray.direction;
        Vector3 reflectDir = (hitNormal * 2.0f * hitNormal.dot(lightDir)) - lightDir;
        float RdotV = std::max(reflectDir.dot(viewDir), 0.0f);
        Color specular = light.intensity * closestSphere->material.Ks * std::pow(RdotV, closestSphere->material.specExp);

        // add contributions
        finalColor = finalColor + (diffuse + specular) * light.intensity;
    }

    // reflection
    if (closestSphere->material.Kr > 0) {
        Vector3 reflectDir = ray.direction.reflect(hitNormal);
        Ray reflectRay(hitPoint + hitNormal * 0.001f, reflectDir);
        Color reflectColor = traceRay(reflectRay, scene, depth + 1);
        finalColor = finalColor + reflectColor * closestSphere->material.Kr;
    }

    finalColor.clamp();
    return finalColor;
}
