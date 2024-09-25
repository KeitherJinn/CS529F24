#include "Matrix4.h"
#include <cmath>
#include <iostream>

using namespace std;

Matrix4::Matrix4()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) data[i][j] = 1;
            else  data[i][j] = 0;
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
    if (cosa < 0.00001) cosa = 0;
    if (sina < 0.00001) sina = 0;
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
    if (cosa < 0.00001) cosa = 0;
    if (sina < 0.00001) sina = 0;
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
    if (cosa < 0.00001) cosa = 0;
    if (sina < 0.00001) sina = 0;
    result.updateElement(0, 0, cosa);
    result.updateElement(1, 1, cosa);
    result.updateElement(0, 1, -sina);
    result.updateElement(1, 0, sina);
    return result;
}