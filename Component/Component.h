#pragma once

class Component
{
public:
    friend class TransientSystem;
    Component(class Entity* owner, int updateOrder);
    virtual ~Component();
    int GetUpdateOrder() const;
    Entity* GetOwner() const { return mOwner; }

    int mUpdateOrder;
protected:
    class Entity* mOwner;
};
