#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Vector.h"
#include "Quaternion.h"
#include <vector>
#include <memory>

// Forward declaration
class Component;

class GameObject {

public:
    Vector3 position;
    Vector3 rotation;

    GameObject(const Vector3& position, const Vector3& rotation)
        : position(position), rotation(rotation) {}

private:
    std::vector<std::shared_ptr<Component>> components;
};

#endif
