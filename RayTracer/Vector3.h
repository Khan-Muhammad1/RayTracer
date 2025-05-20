// Vector3.h
#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>

/**
 * This class does basic vector operaions such as addition , subtraction dot and cross product,
 * normalization and scalling.
 */


class Vector3 {
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Vector operations
    Vector3 operator+(const Vector3& v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    Vector3 operator-(const Vector3& v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }
    Vector3 operator*(float s) const {
        return Vector3(x * s, y * s, z * s);
    }
    Vector3 operator/(float s) const {
        return Vector3(x / s, y / s, z / s);
    }
    Vector3 operator*(const Vector3& v) const { 
        return Vector3(x * v.x, y * v.y, z * v.z);
    }


    Vector3 operator-() const {
        return Vector3(-x, -y, -z);
    }

    // normalize vector
    Vector3& normalize() {
        float len = length();
        if (len > 0) {
            x /= len; y /= len; z /= len;
        }
        return *this;
    }

    // dot product 
    float dot(const Vector3& v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    // reflect vector
    Vector3 reflect(const Vector3& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
    }

    // length of vector
    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

#endif
