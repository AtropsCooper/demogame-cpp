#pragma once
#include "System.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Vector2.h"

class TileMapManager
{
public:
    TileMapManager(Game *game);
    ~TileMapManager();

    void Initialize();
    void ReadMapFromFile(const std::string &fileName);
    void GenerateMap();
    void Instanciate();
    void ClearTileEntities();
    Vector2 GetSpawnPoint();
    Vector2 GetSpawnPointAwayFrom(Vector2 pos, float distance);
    void CleanUp() { mTileEntities.clear(); }

private:
    SDL_Texture* mTileTexture;
    
    class Game* mGame;
    std::vector<class Entity*> mTileEntities;
    unsigned char mTiles[MAPSIZE][MAPSIZE];
}; 