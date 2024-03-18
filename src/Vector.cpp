// Vector3.cpp
#include "Vector.h"
#include <cmath>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3 &other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3 &other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator*(const Vector3 &other) const
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

float Vector3::dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3 &other) const
{
    return Vector3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

float Vector3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}


Vector3 Vector3::normalize() const
{
    float len = length();
    float newx = x;
    float newy = y;
    float newz = z;
    if (len != 0)
    {
        newx /= len;
        newy /= len;
        newz /= len;
    }
    return Vector3(newx, newy, newz);
}
