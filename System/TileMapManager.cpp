#include "TileMapManager.h"
#include "Game.h"
#include "Entity.h"
#include "SpriteComponent.h"

const char FLOOR_NORMAL = 1;
const char WALL_MID = 11;
const char WALL_TOP = 12;
const char WALL_LEFT = 13;
const char WALL_LEFT_TOP = 14;
const char WALL_RIGHT = 15;
const char WALL_RIGHT_TOP = 16;
const char CORNER_LT = 21;
const char CORNER_LB = 22;
const char CORNER_RT = 23;
const char CORNER_RB = 24;

const SDL_Rect R_FLOOR_NORMAL = {16, 64, 16, 16};
const SDL_Rect R_WALL_MID = {32, 16, 16, 16};
const SDL_Rect R_WALL_LEFT = {0, 128, 16, 16};
const SDL_Rect R_WALL_RIGHT = {16, 128, 16, 16};

TileMapManager::TileMapManager(Game *game) : mGame(game)
{
}

TileMapManager::~TileMapManager()
{
    ClearTileEntities();
}

void TileMapManager::Initialize()
{
    mTileTexture = mGame->GetTexture("dungeon");
    memset(mTiles, 0, sizeof(mTiles));
}

void TileMapManager::GenerateMap()
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            mTiles[i][j] = (i == 0 || i == 15 || j == 0 || j == 15) ? WALL_MID : FLOOR_NORMAL;
        }
    }
}

void TileMapManager::Instanciate()
{
    
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (mTiles[i][j] != 0)
            {
                Entity* tile = new Entity(mGame);
                tile->mPosition.x = static_cast<float>(i);
                tile->mPosition.y = static_cast<float>(j);
                mTileEntities.emplace_back(tile);
                SpriteComponent* sprite = new SpriteComponent(tile, 0);
                switch (mTiles[i][j])
                {
                case FLOOR_NORMAL:
                    sprite->SetTexture(mTileTexture, &R_FLOOR_NORMAL);
                    break;
                case WALL_MID:
                    sprite->SetTexture(mTileTexture, &R_WALL_MID);
                    break;

                default:
                    break;
                }
            }
        }
    }
}

void TileMapManager::ClearTileEntities()
{
    for (auto t : mTileEntities)
    {
        t->SetState(Entity::EDead);
    }
    mTileEntities.clear();
}