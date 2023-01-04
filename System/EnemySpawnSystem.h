#pragma once
#include "System.h"
#include "Vector2.h"

class EnemySpawnSystem : public System
{
public:
    EnemySpawnSystem(class Game* game, int order);
    void Update(float deltaTime);
    void SetPlayer(const class Entity* player);

private:
    float mTimeUntilSpawn;
    const class Entity* mPlayer;
    Vector2 mPlayerPos;
};