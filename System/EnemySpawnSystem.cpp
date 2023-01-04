#include "EnemySpawnSystem.h"
#include "Constants.h"
#include "Game.h"
#include "Entity.h"
#include "TileMapManager.h"
#include "AnimComponent.h"
#include "SkeletonPrefab.h"

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
        if ( static_cast<float>(rand()) / static_cast<float>(RAND_MAX) < 1.0f )
        {
            new SkeletonPrefab(mGame, mGame->mTileMapManager->GetSpawnPointAwayFrom(mPlayerPos, 10.0f));
        }

        mTimeUntilSpawn += ENEMY_SPAWN_INTERVAL;
    }
}