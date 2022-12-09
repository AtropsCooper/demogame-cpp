#pragma once
#include "Component.h"

class HostilityComponent : public Component
{
public:
    enum Hostility
    {
        ENeutral = 0,
        EFriend = 1,
        EEnemy = 2
    };
    HostilityComponent(Entity* owner, Hostility hostility) : Component(owner, 500), mHostility(hostility){}
    Hostility mHostility;
};