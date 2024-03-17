/**
 * Quaternion.cpp v1.0.0 30/08/2023
 *
 * Copyright (c) 2023, Robert Eisele (raw.org)
 * Licensed under the MIT license.
 **/

#include "Quaternion.h"
#include "Vector.h"
#include <cmath>
/**
 * Assigns a quaternion to the current quaternion
 */
Quaternion &Quaternion::operator=(const Quaternion &q)
{
	w = q.w;
	x = q.x;
	y = q.y;
	z = q.z;
	return *this;
}

/**
 * Adds two quaternions Q1 and Q2
 */
Quaternion &Quaternion::operator+=(const Quaternion &q)
{
	w += q.w;
	x += q.x;
	y += q.y;
	z += q.z;
	return *this;
}

/**
 * Subtracts a quaternions Q2 from Q1
 */
Quaternion &Quaternion::operator-=(const Quaternion &q)
{
	w -= q.w;
	x -= q.x;
	y -= q.y;
	z -= q.z;
	return *this;
}

/**
 * Scales a quaternion by a scalar
 */
Quaternion &Quaternion::operator*=(float scale)
{
	w *= scale;
	x *= scale;
	y *= scale;
	z *= scale;
	return *this;
}

/**
 * Calculates the Hamilton product of two quaternions
 */
Quaternion &Quaternion::operator*=(const Quaternion &q)
{
	float w1 = w;
	float x1 = x;
	float y1 = y;
	float z1 = z;

	float w2 = q.w;
	float x2 = q.x;
	float y2 = q.y;
	float z2 = q.z;

	w = w1 * w2 - x1 * x2 - y1 * y2 - z1 * z2;
	x = w1 * x2 + x1 * w2 + y1 * z2 - z1 * y2;
	y = w1 * y2 + y1 * w2 + z1 * x2 - x1 * z2;
	z = w1 * z2 + z1 * w2 + x1 * y2 - y1 * x2;
	return *this;
}

/**
 * Calculates the dot product of two quaternions
 */
float Quaternion::dot(const Quaternion &q) const
{
	return w * q.w + x * q.x + y * q.y + z * q.z;
}

/**
 * Calculates the length/modulus/magnitude or the norm of a quaternion
 */
float Quaternion::norm() const
{
	return sqrtf(w * w + x * x + y * y + z * z);
}

/**
 * Calculates the squared length/modulus/magnitude or the norm of a quaternion
 */
float Quaternion::normSq() const
{
	return w * w + x * x + y * y + z * z;
}

/**
 * Normalizes the quaternion to have |Q| = 1 as long as the norm is not zero
 */
Quaternion &Quaternion::normalize()
{
	float iLen = 1 / norm();
	w *= iLen;
	x *= iLen;
	y *= iLen;
	z *= iLen;
	return *this;
}

/**
 * Calculates the conjugate of a quaternion
 */
const Quaternion Quaternion::conjugate() const
{
	return Quaternion(this->w, -this->x, -this->y, -this->z);
}

/**
 * Rotates a vector according to the current quaternion, assumes |q|=1
 *
 * @link https://raw.org/proof/vector-rotation-using-quaternions/
 */
const Vector3 Quaternion::rotateVector(float vx, float vy, float vz)
{
    // Create a pure quaternion representing the vector to rotate
    Quaternion p(0, vx, vy, vz);

    // Perform the rotation using the Hamilton product (q^-1 * p * q)
    Quaternion rotated = this->conjugate().hamiltonProduct(p).hamiltonProduct(*this);

    // Extract the rotated vector components
    return Vector3(rotated.x, rotated.y, rotated.z);
}


// Helper function for the Hamilton product
const Quaternion Quaternion::hamiltonProduct(const Quaternion& other) const {
    Quaternion result;
    result.w = this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z;
    result.x = this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y;
    result.y = this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x;
    result.z = this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w;
    return result;
}

/**
 * Creates a quaternion by a rotation given by Euler angles (multiplication order from right to left)
 *
 * If needed, define QUATERNION_EULER_ORDER for another order
 */
const Quaternion Quaternion::fromEuler(float x, float y, float z) {
    // Convert degrees to radians
    x *= (3.14f / 180.0f);
    y *= (3.14f / 180.0f);
    z *= (3.14f/ 180.0f);

    // Pre-calculate half angles for efficiency
    float cx = cos(x / 2.0f);
    float cy = cos(y / 2.0f);
    float cz = cos(z / 2.0f);
    float sx = sin(x / 2.0f);
    float sy = sin(y / 2.0f);
    float sz = sin(z / 2.0f);

    // Create the quaternion based on ZYX rotation order
    Quaternion q;
    q.x = sx * cy * cz + cx * sy * sz;
    q.y = cx * sy * cz - sx * cy * sz;
    q.z = cx * cy * sz + sx * sy * cz;
    q.w = cx * cy * cz - sx * sy * sz;

    return q;
}

const Vector3 Quaternion::toEuler(float x, float y, float z, float w)
{
    Vector3 euler = Vector3();

    // Roll (x-axis rotation)
    float sinr_cosp = 2 * (w * x + y * z);
    float cosr_cosp = 1 - 2 * (x * x + y * y);
    euler.x = atan2(sinr_cosp, cosr_cosp);

    // Pitch (y-axis rotation)
    float sinp = 2 * (w * y - z * x);
    if (fabs(sinp) >= 1)
        euler.y = copysign(3.14159265358979323846 / 2, sinp); // Use 90 degrees if out of range
    else
        euler.y = asin(sinp);

    // Yaw (z-axis rotation)
    float siny_cosp = 2 * (w * z + x * y);
    float cosy_cosp = 1 - 2 * (y * y + z * z);
    euler.z = atan2(siny_cosp, cosy_cosp);

    return euler;
}

const Quaternion Quaternion::inverse()
{
	return Quaternion(-x, -y, -z, -w);
}


/**
 * Creates quaternion by a rotation given as axis-angle orientation
 */
const Quaternion Quaternion::fromAxisAngle(float x, float y, float z, float angle)
{
	Quaternion ret;

	float halfAngle = angle * 0.5;

	float sin_2 = sinf(halfAngle);
	float cos_2 = cosf(halfAngle);

	float sin_norm = sin_2 / sqrtf(x * x + y * y + z * z);

	ret.w = cos_2;
	ret.x = x * sin_norm;
	ret.y = y * sin_norm;
	ret.z = z * sin_norm;

	return ret;
}
