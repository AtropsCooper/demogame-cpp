#include "Entity.h"
#include "Game.h"
#include "Component.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "AnimationSystem.h"

Entity::Entity(class Game* game)
    : mPosition(Vector2::Zero)
    , mScale(1.0f)
    , mRotation(0.0f)
    , mState(EActive)
    , mGame(game)
{
    mGame->AddEntity(this);
}

Entity::~Entity()
{
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
    if (mState == EActive)
    {
        mGame->ComponentMessage(component, true);
    }
}

void Entity::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
        if (mState == EActive)
        {
            mGame->ComponentMessage(component, false);
        }
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

void Entity::SetState(enum State state)
{
    if (mState == EActive && state != EActive)
    {
        for (auto c : mComponents)
        {
            mGame->ComponentMessage(c, false);
        }
    }

    if (mState != EActive && state == EActive)
    {
        for (auto c : mComponents)
        {
            mGame->ComponentMessage(c, true);
        }
    }
    mState = state;
}

Entity::State Entity::GetState() const
{
    return mState;
}

#define tGetComponent(type) template type* Entity::GetComponent<type>() const

tGetComponent(SpriteComponent);
tGetComponent(MoveComponent);
tGetComponent(AnimComponent);