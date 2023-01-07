#pragma once
#include "Component.h"
#include "Constants.h"

class AttackComponent : public Component
{
public:
    AttackComponent(class Entity* owner, int order) : Component(owner, order), interval(ATTACK_INTERVAL), cooldown(ATTACK_INTERVAL) {}

    float interval; // How long does an attack take
    float cooldown; // How long until next attack
    float rotation; // rotaiton before attack
};