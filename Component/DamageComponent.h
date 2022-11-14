#pragma once
#include "Component.h"

class DamageComponent : public Component
{
public:
    DamageComponent(class Entity *owner, float damage) : Component(owner, 100), mDamage(damage) {}
    float mDamage;
};