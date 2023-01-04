#pragma once
#include "Component.h"

class AttackComponent : public Component
{
public:
    AttackComponent(class Entity* owner, int order) : Component(owner, order), interval(0.4f), cooldown(0.4f) {}

    float interval; // How long does an attack take
    float cooldown; // How long until next attack
    float rotation; // rotaiton before attack
};