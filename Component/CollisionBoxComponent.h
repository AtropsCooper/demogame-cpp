#pragma once
#include "Component.h"
#include "Vector2.h"

class CollisionBoxComponent : public Component
{
public:
    CollisionBoxComponent(class Entity* owner, int order);

    float mWidth;
    float mHeight;
    Vector2 mOffset;
};