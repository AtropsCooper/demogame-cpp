#pragma once
#include "System.h"

class AISystem : public System
{
public:
    AISystem(class Game* game, int updateOrder) : System(game, updateOrder), mPlayer(nullptr) {}
    void FetchComponents() override;
    void Update(float deltaTime) override;
    void SetPlayer(class Entity* player) { mPlayer = player; }
    void CleanUp() override { mAIs.clear(); }

private:
    std::vector<class AIComponent*> mAIs;
    class Entity* mPlayer;
};
