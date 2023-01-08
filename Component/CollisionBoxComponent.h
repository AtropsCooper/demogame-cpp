#pragma once
#include "Component.h"
#include "Vector2.h"

class CollisionBoxComponent : public Component
{
public:
    CollisionBoxComponent(class Entity *owner, int order);
    Vector2 GetPosition();
    float GetLeft();
    float GetRight();
    float GetTop();
    float GetBottom();

    float mWidth;
    float mHeight;
    Vector2 mOffset;
};