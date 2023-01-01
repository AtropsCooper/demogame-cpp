#pragma once
#include "Component.h"

class DeadOnCollisionComponent : public Component
{
public:
    DeadOnCollisionComponent(class Entity *owner) : Component(owner, 10) {}
};