#pragma once
#include "Component.h"
#include "Entity.h"

class TransientComponent : public Component
{
public:
    explicit TransientComponent(Entity *owner, int order, float life, Entity::State bury) : Component(owner, order), mLifespan(life), mBury(bury) {}
    float mLifespan;
    Entity::State mBury;
};