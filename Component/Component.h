#pragma once

class Component
{
public:
    template<typename T> static bool IsComponent(class Component const* component);

    Component(class Entity* owner);
    virtual ~Component();
    int GetUpdateOrder() const;
    Entity* GetOwner() const { return mOwner; }

protected:
    class Entity* mOwner;
    int mUpdateOrder;
};
