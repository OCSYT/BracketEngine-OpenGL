#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"
#include "Quaternion.h"
#include <vector>
#include <memory>


class GameObject {

public:
    Vector3 position;
    Vector3 rotation;
    Vector3 scale; // New member variable for scale

    GameObject(const Vector3& position, const Vector3& rotation, const Vector3& scale)
        : position(position), rotation(rotation), scale(scale) {}

private:

};

#endif
