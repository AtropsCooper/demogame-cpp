#include "Component.h"
#include "Entity.h"


Component::Component(class Entity* owner)
    : mOwner(owner)
    , mUpdateOrder(100)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

int Component::GetUpdateOrder() const
{
    return mUpdateOrder;
}