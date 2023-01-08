#include "Component.h"
#include "Entity.h"

Component::Component(class Entity *owner, int updateOrder)
    : mUpdateOrder(updateOrder), mOwner(owner)
{
    mOwner->AddComponent(this);
}

Component::~Component()
{
    if (mOwner != nullptr)
    {
        mOwner->RemoveComponent(this);
    }
}

int Component::GetUpdateOrder() const
{
    return mUpdateOrder;
}