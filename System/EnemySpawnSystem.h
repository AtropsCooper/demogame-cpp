#pragma once
#include "System.h"

class EnemySpawnSystem : public System
{
public:
    EnemySpawnSystem(class Game* game, int order);
    void Update(float deltaTime);

private:
    float mTimeUntilSpawn;
    class Entity *mPlayer;
};