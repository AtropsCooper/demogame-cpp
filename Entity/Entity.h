#pragma once
#include "Vector2.h"
#include <vector>
#include "Game.h"

class Entity
{
public:
    enum State
    {
        EActive,
        EPaused,
        EDead
    };

    // Transform Component
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation; // Radian

    Entity(class Game* game);
    virtual ~Entity();

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    template<typename T> T* GetComponent() const;

protected:
    std::vector<class Component*> mComponents;
    class Game* mGame;
};