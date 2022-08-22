#pragma once
#include "System.h"

class PlayerControllerSystem : System
{
public:
    PlayerControllerSystem(Game* game, int updateorder) : System(game, updateorder) {}
    void SetPlayer(class Entity* player);
    void Update(float deltaTime) override;

private:
    class Entity* mPlayer;
    class MoveComponent* mPMC;
};