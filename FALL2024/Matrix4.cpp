#include "Matrix4.h"
#include "Vector3.h"
#include <cmath>
#include <iostream>

using namespace std;

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) data[i][j] = 1.0f;
            else  data[i][j] = 0.0f;
        }
    }
}

void Matrix4::updateElement(int row, int col, float value)
{
    data[row][col] = value;
}

float Matrix4::getElement(int row, int col) const
{
    return data[row][col];
}

Matrix4 Matrix4::operator*(const Matrix4& other)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.updateElement(i, j, 0);
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

Vector3 Matrix4::operator*(const Vector3& vec) const
{
    float x = 0, y = 0, z = 0;
    float temp[4][1] = { vec.x,vec.y,vec.z,1 };
    float temp1[4][1] = { 0,0,0,0 };
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 4; k++) {
            temp1[i][0] += data[i][k] * temp[k][0];
        }
    }
    x = temp1[0][0];
    y = temp1[1][0];
    z = temp1[2][0];
    return Vector3(x, y, z);
}

Matrix4 Matrix4::translation(float tx, float ty, float tz)
{
    Matrix4 result;
    result.updateElement(0, 3, tx);
    result.updateElement(1, 3, ty);
    result.updateElement(2, 3, tz);
    return result;
}

Matrix4 Matrix4::scale(float sx, float sy, float sz)
{
    Matrix4 result;
    result.updateElement(0, 0, sx);
    result.updateElement(1, 1, sy);
    result.updateElement(2, 2, sz);
    return result;
}

Matrix4 Matrix4::rotationX(float angle)
{
    Matrix4 result;
    float cosa = cos(angle);
    float sina = sin(angle);
    result.updateElement(1, 1, cosa);
    result.updateElement(2, 2, cosa);
    result.updateElement(1, 2, -sina);
    result.updateElement(2, 1, sina);
    return result;
}

Matrix4 Matrix4::rotationY(float angle)
{
    Matrix4 result;
    float cosa = cos(angle);
    float sina = sin(angle);
    result.updateElement(0, 0, cosa);
    result.updateElement(2, 2, cosa);
    result.updateElement(2, 0, -sina);
    result.updateElement(0, 2, sina);
    return result;
}

Matrix4 Matrix4::rotationZ(float angle)
{
    Matrix4 result;
    float cosa = cos(angle);
    float sina = sin(angle);
    result.updateElement(0, 0, cosa);
    result.updateElement(1, 1, cosa);
    result.updateElement(0, 1, -sina);
    result.updateElement(1, 0, sina);
    return result;
}

Matrix4 Matrix4::rotationXYZ(float x, float y, float z) {
    return rotationZ(z) * rotationY(y) * rotationX(x);
}

Matrix4 Matrix4::orthographic(float l, float r, float b, float t, float n, float f) {
    Matrix4 res;
    res.data[0][0] = 2.0f / (r - l);
    res.data[1][1] = 2.0f / (t - b);
    res.data[2][2] = -2.0f / (f - n);
    res.data[0][3] = -(r + l) / (r - l);
    res.data[1][3] = -(t + b) / (t - b);
    res.data[2][3] = -(f + n) / (f - n);
    res.data[3][3] = 1.0f;
    return res;
}

Matrix4 Matrix4::perspective(float fov, float aR, float n, float f) {
    Matrix4 res;
    float tanHalFov = tan(fov / 2.0f);
    res.data[0][0] = 1.0f / (aR * tanHalFov);
    res.data[1][1] = 1.0f / tanHalFov;
    res.data[2][2] = -(f + n) / (f - n);
    res.data[2][3] = -(2.0f * f * n) / (f - n);
    res.data[3][2] = -1.0f;
    res.data[3][3] = 0.0f;
    return res;
}

Matrix4 Matrix4::lookAt(const Vector3& eye, const Vector3 center, const Vector3 up) {
    Vector3 f = (center - eye).normalized();
    Vector3 s = f.cross(up.normalized());
    Vector3 u = s.cross(f);

    Matrix4 res;
    res.data[0][0] = s.x;
    res.data[1][0] = s.y;
    res.data[2][0] = s.z;
    res.data[0][1] = u.x;
    res.data[1][1] = u.y;
    res.data[2][1] = u.z;
    res.data[0][2] = -f.x;
    res.data[1][2] = -f.y;
    res.data[2][2] = -f.z;
    res.data[3][0] = -s.dot(eye);
    res.data[3][1] = -u.dot(eye);
    res.data[3][2] = f.dot(eye);
    res.data[3][3] = -1.0f;
    return res;
}

const float* Matrix4::getData() const {
    return &data[0][0];
}