#pragma once
#include "Component.h"
#include "Entity.h"

class TransientComponent : public Component
{
public:
    TransientComponent(Entity *owner, int order, float life) : Component(owner, order), mLifespan(life) {}
    float mLifespan;
    virtual void Bury()
    {
        delete this;
    };
};