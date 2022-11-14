#pragma once
#include "System.h"
#include <vector>
#include <utility>

class DamageSystem : public System
{
public:
    DamageSystem(class Game* game, int order);
    void FetchComponents() override;
    void Update(float deltaTime) override;
private:
    std::vector<std::pair<class Entity*, class Entity*>> mColliders;
};