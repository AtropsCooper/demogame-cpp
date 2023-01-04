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
    void CleanUp() override { mColliders.clear(); }
private:
    std::vector<std::pair<class Entity*, class Entity*>> mColliders;
};