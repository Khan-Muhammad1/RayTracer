#include "Matrix4x4.h"

Matrix4x4::Matrix4x4() {
    // Initialize to zero
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = 0.0;
}

Matrix4x4::Matrix4x4(const double mat[4][4]) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = mat[i][j];
}

// identity matrix 
Matrix4x4 Matrix4x4::identity() {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i)
        result.m[i][i] = 1.0;
    return result;
}

// scaling matrix
Matrix4x4 Matrix4x4::scaling(double sx, double sy, double sz) {
    Matrix4x4 result = Matrix4x4::identity();
    result.m[0][0] = sx;
    result.m[1][1] = sy;
    result.m[2][2] = sz;
    return result;
}

//translation matrix
Matrix4x4 Matrix4x4::translation(double tx, double ty, double tz) {
    Matrix4x4 result = Matrix4x4::identity();
    result.m[0][3] = tx;
    result.m[1][3] = ty;
    result.m[2][3] = tz;
    return result;
}

// inverse of matrix
Matrix4x4 Matrix4x4::inverse() const {
    Matrix4x4 invMat;
    invert_matrix(const_cast<double(*)[4]>(m), invMat.m);
    return invMat;
}

// transpose of matrix
Matrix4x4 Matrix4x4::transpose() const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            result.m[i][j] = m[j][i];
    return result;
}

// applies transformation to a point
Vector3 Matrix4x4::transformPoint(const Vector3& v) const {
    double x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3];
    double y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3];
    double z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3];
    double w = m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3];

    if (w != 1.0 && w != 0.0) {
        x /= w;
        y /= w;
        z /= w;
    }

    return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Vector3 Matrix4x4::transformVector(const Vector3& v) const {
    double x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z;
    double y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z;
    double z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z;

    return Vector3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0.0;
            for (int k = 0; k < 4; ++k)
                result.m[i][j] += m[i][k] * other.m[k][j];
        }
    return result;
}
