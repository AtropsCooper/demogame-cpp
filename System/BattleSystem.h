#pragma once
#include "System.h"
#include "AttackComponent.h"

class BattleSystem : public System
{
public:
    BattleSystem(class Game* game, int order);

    void FetchComponents() override;
    void Update(float deltaTime) override;

private:
    std::vector<AttackComponent*> mAttackComponents;
};