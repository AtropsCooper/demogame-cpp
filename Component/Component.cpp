#include "Component.h"
#include "Entity.h"

template<typename T> bool Component::IsComponent(class Component const* c)
{
    if (dynamic_cast<const T*>(c) != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}



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