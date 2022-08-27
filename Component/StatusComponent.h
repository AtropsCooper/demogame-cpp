#pragma once
#include "Component.h"

class StatusComponent : Component
{
public:
    StatusComponent(class Entity* owner, int order) : Component(owner, order) {}
    float mHealth;
};