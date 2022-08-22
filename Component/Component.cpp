#include "Component.h"
#include "Entity.h"

Component::Component(class Entity* owner, int updateOrder)
    : mOwner(owner)
    , mUpdateOrder(updateOrder)
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