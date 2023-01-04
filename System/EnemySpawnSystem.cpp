#include "EnemySpawnSystem.h"
#include "Constants.h"
#include "Game.h"
#include "Entity.h"
#include "TileMapManager.h"
#include "AnimComponent.h"
#include "SkeletonPrefab.h"
#include "GoblinPrefab.h"
#include "DemonPrefab.h"
#include "BossPrefab.h"

EnemySpawnSystem::EnemySpawnSystem(class Game* game, int order)
    : System(game, order)
    , mTimeUntilSpawn(0.0f)
    , mPlayer(nullptr)
    , mPlayerPos()
{

}

void EnemySpawnSystem::SetPlayer(const Entity* player)
{
    mPlayer = player;
}


void EnemySpawnSystem::Update(float deltaTime)
{
    if (mPlayer != nullptr)
    {
        mPlayerPos = mPlayer->mPosition;
    }

    mTimeUntilSpawn -= deltaTime;
    if (mTimeUntilSpawn <= 0)
    {
        if ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < ENEMY_SPAWN_RATE )
        {
            SpawnEnemies(1);
        }

        mTimeUntilSpawn += ENEMY_SPAWN_INTERVAL;
    }
}

void EnemySpawnSystem::SpawnEnemies(int number)
{
    for (int counter = 0; counter < number; counter ++)
    {
        int roll = rand() % 6;
        switch (roll)
        {
        case 0:
        case 1:
        case 2:
            new SkeletonPrefab(mGame, mGame->mTileMapManager->GetSpawnPointAwayFrom(mPlayerPos, ENEMY_SPAWN_RANGE));
            break;
        case 3:
        case 4:
            new GoblinPrefab(mGame, mGame->mTileMapManager->GetSpawnPointAwayFrom(mPlayerPos, ENEMY_SPAWN_RANGE));
            break;
        case 5:
            new DemonPrefab(mGame, mGame->mTileMapManager->GetSpawnPointAwayFrom(mPlayerPos, ENEMY_SPAWN_RANGE));
            break;
        }
    }

}

Entity* EnemySpawnSystem::SpawnBoss()
{
    return new BossPrefab(mGame, mGame->mTileMapManager->GetSpawnPointAwayFrom(mPlayerPos, ENEMY_SPAWN_RANGE * 2));
}