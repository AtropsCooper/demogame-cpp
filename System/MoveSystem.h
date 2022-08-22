#pragma once
#include "System.h"
#include "MoveComponent.h"
#include "Vector2.h"
#include <vector>

class MoveSystem : public System
{
public:
    MoveSystem(class Game* game, int updateOrder) : System(game, updateOrder) {}
    void FetchComponents() override;
    void Update(float deltaTime) override;

private:
    std::vector<class MoveComponent*> mMoveComponents;
};