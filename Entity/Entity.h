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
    Vector2 mPosition;
    float mScale;
    float mRotation; // Radian

    Entity(class Game* game);
    virtual ~Entity();

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);
    template<typename T> T* GetComponent() const;
    void SetState(enum State state);
    enum State GetState() const;

protected:
    State mState;
    std::vector<class Component*> mComponents;
    class Game* mGame;
};