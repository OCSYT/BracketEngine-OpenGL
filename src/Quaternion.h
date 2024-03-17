/**
 * Quaternion.cpp v1.0.0 30/08/2023
 *
 * Copyright (c) 2023, Robert Eisele (raw.org)
 * Licensed under the MIT license.
 **/

#ifndef QUATERNION_H
#define QUATERNION_H
#include <math.h>
#include "Vector.h"
class Quaternion
{
public:
    float w;
    float x;
    float y;
    float z;

    /* @TODO
        union {
        struct {
            float x;
            float y;
            float z;
        };
        real_t vector[3] = { 0, 0, 0 };
    };
    */

    Quaternion() : w(1), x(0), y(0), z(0) {}
    Quaternion(const Quaternion &q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
    Quaternion(float _x, float _y, float _z) : w(0), x(_x), y(_y), z(_z) {}
    Quaternion(float _w, float _x, float _y, float _z) : w(_w), x(_x), y(_y), z(_z) {}

    Quaternion &operator=(const Quaternion &rhs);
    Quaternion &operator+=(const Quaternion &q);
    Quaternion &operator-=(const Quaternion &q);
    Quaternion &operator*=(float scale);
    Quaternion &operator*=(const Quaternion &q);

    

    const Quaternion operator-() const { return Quaternion(-w, -x, -y, -z); }
    const Quaternion operator*(const Quaternion &b) const { return Quaternion(*this) *= b; }
    const Quaternion operator*(float scale) const { return Quaternion(w * scale, x * scale, y * scale, z * scale); }
    const Quaternion operator+(const Quaternion &q2) const
    {
        const Quaternion &q1 = *this;
        return Quaternion(q1.w + q2.w, q1.x + q2.x, q1.y + q2.y, q1.z + q2.z);
    }
    const Quaternion operator-(const Quaternion &q2) const
    {
        const Quaternion &q1 = *this;
        return Quaternion(q1.w - q2.w, q1.x - q2.x, q1.y - q2.y, q1.z - q2.z);
    }

    float dot(const Quaternion &q) const;
    float norm() const;
    float normSq() const;
    Quaternion &normalize();
    const Quaternion hamiltonProduct(const Quaternion& other) const;
    const Quaternion conjugate() const; 
    const Vector3 rotateVector(float vx, float vy, float vz);

    const Quaternion inverse();

    static const Quaternion fromEuler(float _x, float _y, float _z);
    static const Vector3 toEuler(float x, float y, float z, float w);
    static const Quaternion fromAxisAngle(float x, float y, float z, float angle);
};

#endif