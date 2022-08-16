#include "Entity.h"
#include "Game.h"
#include "Component.h"

Entity::Entity(class Game* game)
    : mState(EActive)
    , mPosition(Vector2::Zero)
    , mScale(1.0f)
    , mRotation(0.0f)
    , mGame(game)
{
    mGame->AddEntity(this);
}

Entity::~Entity()
{
    mGame->RemoveEntity(this);
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }

}

void Entity::AddComponent(Component* component)
{
    int myOrder = component->GetUpdateOrder();
    auto iter = mComponents.begin();
    for (; iter != mComponents.end(); iter++)
    {
        if (myOrder < (*iter)->GetUpdateOrder())
        {
            break;
        }
    }
    mComponents.insert(iter, component);
}

void Entity::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

// Need change:
// Deal with multiple components of same class
template<typename T> T* Entity::GetComponent() const
{
    for (auto c : mComponents)
    {
        T* component = dynamic_cast<T*>(c);
        if (component != nullptr)
        {
            return component;
        }
    }
    return nullptr;
}