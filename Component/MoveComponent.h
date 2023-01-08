#pragma once
#include "Component.h"
#include "Vector2.h"

class MoveComponent : public Component
{
public:
    MoveComponent(Entity *owner, int updateOrder) : Component(owner, updateOrder) {}
    Vector2 mVelocity;
};