#pragma once
#include "TransientComponent.h"

class SuicideComponent : public TransientComponent
{
public:
    SuicideComponent(Entity *owner, int order, float life) : TransientComponent(owner, order, life) {}
    virtual void Bury() override
    {
        mOwner->SetState(Entity::EDead);
    }
};