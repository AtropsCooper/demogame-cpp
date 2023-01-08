#pragma once
#include "Component.h"

class AIComponent : public Component
{
public:
    enum Pattern
    {
        EFollow,
        EHelix,
        ERevHelix
    };
    AIComponent(class Entity *owner, float speed, Pattern pattern)
        : Component(owner, 100), mSpeed(speed), mPattern(pattern) {}
    float mSpeed;
    Pattern mPattern;
};