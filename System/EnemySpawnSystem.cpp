#include "EnemySpawnSystem.h"
#include "Constants.h"
#include "Game.h"
#include "Entity.h"
#include "AnimComponent.h"
#include "SkeletonPrefab.h"

EnemySpawnSystem::EnemySpawnSystem(class Game* game, int order)
    : System(game, order)
    , mTimeUntilSpawn(0.0f)
{

}


void EnemySpawnSystem::Update(float deltaTime)
{
    mPlayer = mGame->mPlayer;

    auto PickSpawnPoint = [](float playerX, float playerY) -> Vector2
    {
        Vector2 spawnPoint;
        spawnPoint.x = playerX + static_cast<float>(rand() % static_cast<int>(ENEMY_SPAWN_RANGE)) * ((rand() % 2) * 2 - 1);
        spawnPoint.y = playerY + static_cast<float>(rand() % static_cast<int>(ENEMY_SPAWN_RANGE)) * ((rand() % 2) * 2 - 1);
        return spawnPoint;
    };

    mTimeUntilSpawn -= deltaTime;
    if (mTimeUntilSpawn <= 0)
    {
        if ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < 1.0f )
        {
            Vector2 spawnPoint = PickSpawnPoint(mPlayer->mPosition.x, mPlayer->mPosition.y);
            new SkeletonPrefab(mGame, spawnPoint);
        }

        mTimeUntilSpawn += ENEMY_SPAWN_INTERVAL;
    }
}